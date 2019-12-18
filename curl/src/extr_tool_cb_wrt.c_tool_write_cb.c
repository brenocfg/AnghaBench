#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct OutStruct {int bytes; scalar_t__ stream; scalar_t__ init; scalar_t__ is_cd_filename; scalar_t__ alloc_filename; scalar_t__ fopened; scalar_t__ s_isreg; int /*<<< orphan*/ * filename; struct OperationConfig* config; } ;
struct per_transfer {int /*<<< orphan*/  curl; struct OutStruct outs; } ;
struct OperationConfig {int readbusy; scalar_t__ nobuffer; int /*<<< orphan*/  synthetic_error; TYPE_1__* global; int /*<<< orphan*/  terminal_binary_ok; scalar_t__ show_headers; } ;
struct TYPE_2__ {int isatty; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  CURLPAUSE_CONT ; 
 scalar_t__ CURL_MAX_HTTP_HEADER ; 
 scalar_t__ CURL_MAX_WRITE_SIZE ; 
 int /*<<< orphan*/  ERR_BINARY_TERMINAL ; 
 void* FALSE ; 
 scalar_t__ GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  WriteConsoleW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 intptr_t _get_osfhandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_easy_pause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 char* curlx_getenv (char*) ; 
 int fflush (scalar_t__) ; 
 int /*<<< orphan*/  fileno (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 size_t fwrite (char*,size_t,size_t,scalar_t__) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ memchr (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tool_create_output_file (struct OutStruct*) ; 
 int /*<<< orphan*/  warnf (TYPE_1__*,char*) ; 

size_t tool_write_cb(char *buffer, size_t sz, size_t nmemb, void *userdata)
{
  size_t rc;
  struct per_transfer *per = userdata;
  struct OutStruct *outs = &per->outs;
  struct OperationConfig *config = outs->config;
  size_t bytes = sz * nmemb;
  bool is_tty = config->global->isatty;
#ifdef WIN32
  CONSOLE_SCREEN_BUFFER_INFO console_info;
  intptr_t fhnd;
#endif

  /*
   * Once that libcurl has called back tool_write_cb() the returned value
   * is checked against the amount that was intended to be written, if
   * it does not match then it fails with CURLE_WRITE_ERROR. So at this
   * point returning a value different from sz*nmemb indicates failure.
   */
  const size_t failure = bytes ? 0 : 1;

#ifdef DEBUGBUILD
  {
    char *tty = curlx_getenv("CURL_ISATTY");
    if(tty) {
      is_tty = TRUE;
      curl_free(tty);
    }
  }

  if(config->show_headers) {
    if(bytes > (size_t)CURL_MAX_HTTP_HEADER) {
      warnf(config->global, "Header data size exceeds single call write "
            "limit!\n");
      return failure;
    }
  }
  else {
    if(bytes > (size_t)CURL_MAX_WRITE_SIZE) {
      warnf(config->global, "Data size exceeds single call write limit!\n");
      return failure;
    }
  }

  {
    /* Some internal congruency checks on received OutStruct */
    bool check_fails = FALSE;
    if(outs->filename) {
      /* regular file */
      if(!*outs->filename)
        check_fails = TRUE;
      if(!outs->s_isreg)
        check_fails = TRUE;
      if(outs->fopened && !outs->stream)
        check_fails = TRUE;
      if(!outs->fopened && outs->stream)
        check_fails = TRUE;
      if(!outs->fopened && outs->bytes)
        check_fails = TRUE;
    }
    else {
      /* standard stream */
      if(!outs->stream || outs->s_isreg || outs->fopened)
        check_fails = TRUE;
      if(outs->alloc_filename || outs->is_cd_filename || outs->init)
        check_fails = TRUE;
    }
    if(check_fails) {
      warnf(config->global, "Invalid output struct data for write callback\n");
      return failure;
    }
  }
#endif

  if(!outs->stream && !tool_create_output_file(outs))
    return failure;

  if(is_tty && (outs->bytes < 2000) && !config->terminal_binary_ok) {
    /* binary output to terminal? */
    if(memchr(buffer, 0, bytes)) {
      warnf(config->global, "Binary output can mess up your terminal. "
            "Use \"--output -\" to tell curl to output it to your terminal "
            "anyway, or consider \"--output <FILE>\" to save to a file.\n");
      config->synthetic_error = ERR_BINARY_TERMINAL;
      return failure;
    }
  }

#ifdef WIN32
  fhnd = _get_osfhandle(fileno(outs->stream));
  if(isatty(fileno(outs->stream)) &&
     GetConsoleScreenBufferInfo((HANDLE)fhnd, &console_info)) {
    DWORD in_len = (DWORD)(sz * nmemb);
    wchar_t* wc_buf;
    DWORD wc_len;

    /* calculate buffer size for wide characters */
    wc_len = MultiByteToWideChar(CP_UTF8, 0, buffer, in_len,  NULL, 0);
    wc_buf = (wchar_t*) malloc(wc_len * sizeof(wchar_t));
    if(!wc_buf)
      return failure;

    /* calculate buffer size for multi-byte characters */
    wc_len = MultiByteToWideChar(CP_UTF8, 0, buffer, in_len, wc_buf, wc_len);
    if(!wc_len) {
      free(wc_buf);
      return failure;
    }

    if(!WriteConsoleW(
        (HANDLE) fhnd,
        wc_buf,
        wc_len,
        &wc_len,
        NULL)) {
      free(wc_buf);
      return failure;
    }
    free(wc_buf);
    rc = bytes;
  }
  else
#endif
    rc = fwrite(buffer, sz, nmemb, outs->stream);

  if(bytes == rc)
    /* we added this amount of data to the output */
    outs->bytes += bytes;

  if(config->readbusy) {
    config->readbusy = FALSE;
    curl_easy_pause(per->curl, CURLPAUSE_CONT);
  }

  if(config->nobuffer) {
    /* output buffering disabled */
    int res = fflush(outs->stream);
    if(res)
      return failure;
  }

  return rc;
}