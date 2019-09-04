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
struct TYPE_2__ {char* set; char* in; scalar_t__ pcode; scalar_t__ ucode; int /*<<< orphan*/  out; int /*<<< orphan*/  setflags; int /*<<< orphan*/  urlflags; } ;
typedef  scalar_t__ CURLUcode ;
typedef  int /*<<< orphan*/  CURLU ;

/* Variables and functions */
 scalar_t__ CURLUE_OK ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 scalar_t__ checkurl (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_url_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 TYPE_1__* set_parts_list ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ updateurl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_parts(void)
{
  int i;
  CURLUcode rc;
  int error = 0;

  for(i = 0; set_parts_list[i].set && !error; i++) {
    char *url = NULL;
    CURLU *urlp = curl_url();
    if(!urlp) {
      error++;
      break;
    }
    if(set_parts_list[i].in)
      rc = curl_url_set(urlp, CURLUPART_URL, set_parts_list[i].in,
                        set_parts_list[i].urlflags);
    else
      rc = CURLUE_OK;
    if(!rc) {
      CURLUcode uc = updateurl(urlp, set_parts_list[i].set,
                               set_parts_list[i].setflags);

      if(uc != set_parts_list[i].pcode) {
        fprintf(stderr, "updateurl\nin: %s\nreturned %d (expected %d)\n",
                set_parts_list[i].set, (int)uc, set_parts_list[i].pcode);
        error++;
      }

      rc = curl_url_get(urlp, CURLUPART_URL, &url, 0);

      if(rc) {
        fprintf(stderr, "%s:%d Get URL returned %d\n",
                __FILE__, __LINE__, (int)rc);
        error++;
      }
      else if(checkurl(url, set_parts_list[i].out)) {
        error++;
      }
    }
    else if(rc != set_parts_list[i].ucode) {
      fprintf(stderr, "Set parts\nin: %s\nreturned %d (expected %d)\n",
              set_parts_list[i].in, (int)rc, set_parts_list[i].ucode);
      error++;
    }
    curl_free(url);
    curl_url_cleanup(urlp);
  }
  return error;
}