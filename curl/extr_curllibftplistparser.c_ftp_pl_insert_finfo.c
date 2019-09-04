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
struct ftp_wc {struct ftp_parselist_data* parser; } ;
struct TYPE_5__ {int filename; int group; int perm; int symlink_target; int time; int user; } ;
struct ftp_parselist_data {int /*<<< orphan*/ * file_data; TYPE_1__ offsets; } ;
struct TYPE_7__ {char* group; char* perm; char* target; char* time; char* user; } ;
struct curl_fileinfo {char* b_data; char* filename; scalar_t__ filetype; TYPE_3__ strings; } ;
struct fileinfo {int /*<<< orphan*/  list; struct curl_fileinfo info; } ;
struct curl_llist {int /*<<< orphan*/  tail; } ;
struct connectdata {TYPE_4__* data; } ;
struct WildcardData {int /*<<< orphan*/  pattern; struct curl_llist filelist; struct ftp_wc* protdata; } ;
typedef  scalar_t__ (* curl_fnmatch_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ;
struct TYPE_6__ {scalar_t__ (* fnmatch ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  fnmatch_data; } ;
struct TYPE_8__ {TYPE_2__ set; struct WildcardData wildcard; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 scalar_t__ CURLFILETYPE_SYMLINK ; 
 int /*<<< orphan*/  Curl_fileinfo_cleanup (struct fileinfo*) ; 
 scalar_t__ Curl_fnmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Curl_llist_insert_next (struct curl_llist*,int /*<<< orphan*/ ,struct curl_fileinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_set_in_callback (TYPE_4__*,int) ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static CURLcode ftp_pl_insert_finfo(struct connectdata *conn,
                                    struct fileinfo *infop)
{
  curl_fnmatch_callback compare;
  struct WildcardData *wc = &conn->data->wildcard;
  struct ftp_wc *ftpwc = wc->protdata;
  struct curl_llist *llist = &wc->filelist;
  struct ftp_parselist_data *parser = ftpwc->parser;
  bool add = TRUE;
  struct curl_fileinfo *finfo = &infop->info;

  /* move finfo pointers to b_data */
  char *str = finfo->b_data;
  finfo->filename       = str + parser->offsets.filename;
  finfo->strings.group  = parser->offsets.group ?
                          str + parser->offsets.group : NULL;
  finfo->strings.perm   = parser->offsets.perm ?
                          str + parser->offsets.perm : NULL;
  finfo->strings.target = parser->offsets.symlink_target ?
                          str + parser->offsets.symlink_target : NULL;
  finfo->strings.time   = str + parser->offsets.time;
  finfo->strings.user   = parser->offsets.user ?
                          str + parser->offsets.user : NULL;

  /* get correct fnmatch callback */
  compare = conn->data->set.fnmatch;
  if(!compare)
    compare = Curl_fnmatch;

  /* filter pattern-corresponding filenames */
  Curl_set_in_callback(conn->data, true);
  if(compare(conn->data->set.fnmatch_data, wc->pattern,
             finfo->filename) == 0) {
    /* discard symlink which is containing multiple " -> " */
    if((finfo->filetype == CURLFILETYPE_SYMLINK) && finfo->strings.target &&
       (strstr(finfo->strings.target, " -> "))) {
      add = FALSE;
    }
  }
  else {
    add = FALSE;
  }
  Curl_set_in_callback(conn->data, false);

  if(add) {
    Curl_llist_insert_next(llist, llist->tail, finfo, &infop->list);
  }
  else {
    Curl_fileinfo_cleanup(infop);
  }

  ftpwc->parser->file_data = NULL;
  return CURLE_OK;
}