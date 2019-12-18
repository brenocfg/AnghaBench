#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct connectdata* file_descriptor; int /*<<< orphan*/  write_function; } ;
struct ftp_wc {int /*<<< orphan*/  parser; TYPE_2__ backup; } ;
struct connectdata {TYPE_4__* data; } ;
struct WildcardData {struct ftp_wc* protdata; int /*<<< orphan*/  dtor; void* pattern; void* path; void* state; } ;
struct FTP {char* path; } ;
struct TYPE_7__ {scalar_t__ ftp_filemethod; struct connectdata* out; int /*<<< orphan*/  fwrite_func; } ;
struct TYPE_5__ {struct FTP* protop; } ;
struct TYPE_8__ {TYPE_3__ set; struct WildcardData wildcard; TYPE_1__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 void* CURLWC_CLEAN ; 
 int /*<<< orphan*/  Curl_ftp_parselist ; 
 int /*<<< orphan*/  Curl_ftp_parselist_data_alloc () ; 
 int /*<<< orphan*/  Curl_ftp_parselist_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_safefree (void*) ; 
 scalar_t__ FTPFILE_MULTICWD ; 
 scalar_t__ FTPFILE_NOCWD ; 
 int /*<<< orphan*/  ZERO_NULL ; 
 struct ftp_wc* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct ftp_wc*) ; 
 scalar_t__ ftp_parse_url_path (struct connectdata*) ; 
 int /*<<< orphan*/  infof (TYPE_4__*,char*) ; 
 void* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  wc_data_dtor ; 

__attribute__((used)) static CURLcode init_wc_data(struct connectdata *conn)
{
  char *last_slash;
  struct FTP *ftp = conn->data->req.protop;
  char *path = ftp->path;
  struct WildcardData *wildcard = &(conn->data->wildcard);
  CURLcode result = CURLE_OK;
  struct ftp_wc *ftpwc = NULL;

  last_slash = strrchr(ftp->path, '/');
  if(last_slash) {
    last_slash++;
    if(last_slash[0] == '\0') {
      wildcard->state = CURLWC_CLEAN;
      result = ftp_parse_url_path(conn);
      return result;
    }
    wildcard->pattern = strdup(last_slash);
    if(!wildcard->pattern)
      return CURLE_OUT_OF_MEMORY;
    last_slash[0] = '\0'; /* cut file from path */
  }
  else { /* there is only 'wildcard pattern' or nothing */
    if(path[0]) {
      wildcard->pattern = strdup(path);
      if(!wildcard->pattern)
        return CURLE_OUT_OF_MEMORY;
      path[0] = '\0';
    }
    else { /* only list */
      wildcard->state = CURLWC_CLEAN;
      result = ftp_parse_url_path(conn);
      return result;
    }
  }

  /* program continues only if URL is not ending with slash, allocate needed
     resources for wildcard transfer */

  /* allocate ftp protocol specific wildcard data */
  ftpwc = calloc(1, sizeof(struct ftp_wc));
  if(!ftpwc) {
    result = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  /* INITIALIZE parselist structure */
  ftpwc->parser = Curl_ftp_parselist_data_alloc();
  if(!ftpwc->parser) {
    result = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  wildcard->protdata = ftpwc; /* put it to the WildcardData tmp pointer */
  wildcard->dtor = wc_data_dtor;

  /* wildcard does not support NOCWD option (assert it?) */
  if(conn->data->set.ftp_filemethod == FTPFILE_NOCWD)
    conn->data->set.ftp_filemethod = FTPFILE_MULTICWD;

  /* try to parse ftp url */
  result = ftp_parse_url_path(conn);
  if(result) {
    goto fail;
  }

  wildcard->path = strdup(ftp->path);
  if(!wildcard->path) {
    result = CURLE_OUT_OF_MEMORY;
    goto fail;
  }

  /* backup old write_function */
  ftpwc->backup.write_function = conn->data->set.fwrite_func;
  /* parsing write function */
  conn->data->set.fwrite_func = Curl_ftp_parselist;
  /* backup old file descriptor */
  ftpwc->backup.file_descriptor = conn->data->set.out;
  /* let the writefunc callback know what curl pointer is working with */
  conn->data->set.out = conn;

  infof(conn->data, "Wildcard - Parsing started\n");
  return CURLE_OK;

  fail:
  if(ftpwc) {
    Curl_ftp_parselist_data_free(&ftpwc->parser);
    free(ftpwc);
  }
  Curl_safefree(wildcard->pattern);
  wildcard->dtor = ZERO_NULL;
  wildcard->protdata = NULL;
  return result;
}