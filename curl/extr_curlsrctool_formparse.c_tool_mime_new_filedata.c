#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* data; int /*<<< orphan*/  kind; scalar_t__ curpos; scalar_t__ size; scalar_t__ origin; } ;
typedef  TYPE_1__ tool_mime ;
struct TYPE_9__ {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__ struct_stat ;
typedef  scalar_t__ curl_off_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_FREE (char const*) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_READ_ERROR ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 scalar_t__ PARAM_OK ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLMIME_FILE ; 
 int /*<<< orphan*/  TOOLMIME_FILEDATA ; 
 int /*<<< orphan*/  TOOLMIME_STDIN ; 
 int /*<<< orphan*/  TOOLMIME_STDINDATA ; 
 scalar_t__ curlx_uztoso (size_t) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ file2memory (char**,size_t*,int /*<<< orphan*/ ) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fstat (int,TYPE_2__*) ; 
 scalar_t__ ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_binmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 TYPE_1__* tool_mime_new (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tool_mime *tool_mime_new_filedata(tool_mime *parent,
                                         const char *filename,
                                         bool isremotefile,
                                         CURLcode *errcode)
{
  CURLcode result = CURLE_OK;
  tool_mime *m = NULL;

  *errcode = CURLE_OUT_OF_MEMORY;
  if(strcmp(filename, "-")) {
    /* This is a normal file. */
    filename = strdup(filename);
    if(filename) {
      m = tool_mime_new(parent, TOOLMIME_FILE);
      if(!m)
        CONST_FREE(filename);
      else {
        m->data = filename;
        if(!isremotefile)
          m->kind = TOOLMIME_FILEDATA;
       *errcode = CURLE_OK;
      }
    }
  }
  else {        /* Standard input. */
    int fd = fileno(stdin);
    char *data = NULL;
    curl_off_t size;
    curl_off_t origin;
    struct_stat sbuf;

    set_binmode(stdin);
    origin = ftell(stdin);
    /* If stdin is a regular file, do not buffer data but read it
       when needed. */
    if(fd >= 0 && origin >= 0 && !fstat(fd, &sbuf) &&
#ifdef __VMS
       sbuf.st_fab_rfm != FAB$C_VAR && sbuf.st_fab_rfm != FAB$C_VFC &&
#endif
       S_ISREG(sbuf.st_mode)) {
      size = sbuf.st_size - origin;
      if(size < 0)
        size = 0;
    }
    else {  /* Not suitable for direct use, buffer stdin data. */
      size_t stdinsize = 0;

      if(file2memory(&data, &stdinsize, stdin) != PARAM_OK) {
        /* Out of memory. */
        return m;
      }

      if(ferror(stdin)) {
        result = CURLE_READ_ERROR;
        Curl_safefree(data);
        data = NULL;
      }
      else if(!stdinsize) {
        /* Zero-length data has been freed. Re-create it. */
        data = strdup("");
        if(!data)
          return m;
      }
      size = curlx_uztoso(stdinsize);
      origin = 0;
    }
    m = tool_mime_new(parent, TOOLMIME_STDIN);
    if(!m)
      Curl_safefree(data);
    else {
      m->data = data;
      m->origin = origin;
      m->size = size;
      m->curpos = 0;
      if(!isremotefile)
        m->kind = TOOLMIME_STDINDATA;
      *errcode = result;
    }
  }
  return m;
}