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
struct TYPE_8__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ struct_stat ;
struct TYPE_9__ {int datasize; int /*<<< orphan*/  kind; int /*<<< orphan*/  freefunc; int /*<<< orphan*/  readfunc; int /*<<< orphan*/  seekfunc; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ curl_mimepart ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_READ_ERROR ; 
 int /*<<< orphan*/  MIMEKIND_FILE ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_part_content (TYPE_2__*) ; 
 scalar_t__ curl_mime_filename (TYPE_2__*,char*) ; 
 int filesize (char const*,TYPE_1__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mime_file_free ; 
 int /*<<< orphan*/  mime_file_read ; 
 int /*<<< orphan*/  mime_file_seek ; 
 scalar_t__ stat (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 char* strippath (char const*) ; 

CURLcode curl_mime_filedata(curl_mimepart *part, const char *filename)
{
  CURLcode result = CURLE_OK;

  if(!part)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  cleanup_part_content(part);

  if(filename) {
    char *base;
    struct_stat sbuf;

    if(stat(filename, &sbuf) || access(filename, R_OK))
      result = CURLE_READ_ERROR;

    part->data = strdup(filename);
    if(!part->data)
      result = CURLE_OUT_OF_MEMORY;

    part->datasize = -1;
    if(!result && S_ISREG(sbuf.st_mode)) {
      part->datasize = filesize(filename, sbuf);
      part->seekfunc = mime_file_seek;
    }

    part->readfunc = mime_file_read;
    part->freefunc = mime_file_free;
    part->kind = MIMEKIND_FILE;

    /* As a side effect, set the filename to the current file's base name.
       It is possible to withdraw this by explicitly calling
       curl_mime_filename() with a NULL filename argument after the current
       call. */
    base = strippath(filename);
    if(!base)
      result = CURLE_OUT_OF_MEMORY;
    else {
      CURLcode res = curl_mime_filename(part, base);

      if(res)
        result = res;
      free(base);
    }
  }
  return result;
}