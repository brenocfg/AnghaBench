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
struct OutStruct {int bytes; int /*<<< orphan*/  stream; struct OperationConfig* config; } ;
struct OperationConfig {scalar_t__ nobuffer; int /*<<< orphan*/  easy; scalar_t__ readbusy; int /*<<< orphan*/  synthetic_error; TYPE_1__* global; int /*<<< orphan*/  terminal_binary_ok; } ;
struct TYPE_2__ {int isatty; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLPAUSE_CONT ; 
 int /*<<< orphan*/  ERR_BINARY_TERMINAL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  curl_easy_pause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fflush (int /*<<< orphan*/ ) ; 
 size_t fwrite (char*,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tool_create_output_file (struct OutStruct*) ; 
 int /*<<< orphan*/  warnf (TYPE_1__*,char*) ; 

size_t tool_write_cb(char *buffer, size_t sz, size_t nmemb, void *userdata)
{
  size_t rc;
  struct OutStruct *outs = userdata;
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
    curl_easy_pause(config->easy, CURLPAUSE_CONT);
  }

  if(config->nobuffer) {
    /* output buffering disabled */
    int res = fflush(outs->stream);
    if(res)
      return failure;
  }

  return rc;
}