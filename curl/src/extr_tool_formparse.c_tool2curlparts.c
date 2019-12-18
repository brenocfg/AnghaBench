#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* filename; int kind; char* data; int /*<<< orphan*/  name; int /*<<< orphan*/  encoder; int /*<<< orphan*/  headers; int /*<<< orphan*/  type; int /*<<< orphan*/  size; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ tool_mime ;
typedef  int /*<<< orphan*/  curl_seek_callback ;
typedef  int /*<<< orphan*/  curl_read_callback ;
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  int /*<<< orphan*/  curl_mime ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURL_ZERO_TERMINATED ; 
#define  TOOLMIME_DATA 133 
#define  TOOLMIME_FILE 132 
#define  TOOLMIME_FILEDATA 131 
#define  TOOLMIME_PARTS 130 
#define  TOOLMIME_STDIN 129 
#define  TOOLMIME_STDINDATA 128 
 scalar_t__ convert_to_network (char*,size_t) ; 
 int /*<<< orphan*/ * curl_mime_addpart (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_mime_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_data_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ curl_mime_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_filedata (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ curl_mime_filename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  curl_mime_free (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_mime_headers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_mime_subparts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ curl_mime_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 scalar_t__ tool2curlmime (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tool_mime_stdin_read ; 
 int /*<<< orphan*/  tool_mime_stdin_seek ; 

__attribute__((used)) static CURLcode tool2curlparts(CURL *curl, tool_mime *m, curl_mime *mime)
{
  CURLcode ret = CURLE_OK;
  curl_mimepart *part = NULL;
  curl_mime *submime = NULL;
  const char *filename = NULL;

  if(m) {
    ret = tool2curlparts(curl, m->prev, mime);
    if(!ret) {
      part = curl_mime_addpart(mime);
      if(!part)
        ret = CURLE_OUT_OF_MEMORY;
    }
    if(!ret) {
      filename = m->filename;
      switch(m->kind) {
      case TOOLMIME_PARTS:
        ret = tool2curlmime(curl, m, &submime);
        if(!ret) {
          ret = curl_mime_subparts(part, submime);
          if(ret)
            curl_mime_free(submime);
        }
        break;

      case TOOLMIME_DATA:
#ifdef CURL_DOES_CONVERSIONS
        /* Our data is always textual: convert it to ASCII. */
        {
          size_t size = strlen(m->data);
          char *cp = malloc(size + 1);

          if(!cp)
            ret = CURLE_OUT_OF_MEMORY;
          else {
            memcpy(cp, m->data, size + 1);
            ret = convert_to_network(cp, size);
            if(!ret)
              ret = curl_mime_data(part, cp, CURL_ZERO_TERMINATED);
            free(cp);
          }
        }
#else
        ret = curl_mime_data(part, m->data, CURL_ZERO_TERMINATED);
#endif
        break;

      case TOOLMIME_FILE:
      case TOOLMIME_FILEDATA:
        ret = curl_mime_filedata(part, m->data);
        if(!ret && m->kind == TOOLMIME_FILEDATA && !filename)
          ret = curl_mime_filename(part, NULL);
        break;

      case TOOLMIME_STDIN:
        if(!filename)
          filename = "-";
        /* FALLTHROUGH */
      case TOOLMIME_STDINDATA:
        ret = curl_mime_data_cb(part, m->size,
                                (curl_read_callback) tool_mime_stdin_read,
                                (curl_seek_callback) tool_mime_stdin_seek,
                                NULL, m);
        break;

      default:
        /* Other cases not possible in this context. */
        break;
      }
    }
    if(!ret && filename)
      ret = curl_mime_filename(part, filename);
    if(!ret)
      ret = curl_mime_type(part, m->type);
    if(!ret)
      ret = curl_mime_headers(part, m->headers, 0);
    if(!ret)
      ret = curl_mime_encoder(part, m->encoder);
    if(!ret)
      ret = curl_mime_name(part, m->name);
  }
  return ret;
}