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
struct TYPE_2__ {char* in; int ucode; int /*<<< orphan*/  out; int /*<<< orphan*/  getflags; int /*<<< orphan*/  urlflags; } ;
typedef  int CURLUcode ;
typedef  int /*<<< orphan*/  CURLU ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUPART_URL ; 
 scalar_t__ checkurl (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 
 int curl_url_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 TYPE_1__* get_url_list ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int get_url(void)
{
  int i;
  CURLUcode rc;
  int error = 0;
  for(i = 0; get_url_list[i].in && !error; i++) {
    char *url = NULL;
    CURLU *urlp = curl_url();
    if(!urlp) {
      error++;
      break;
    }
    rc = curl_url_set(urlp, CURLUPART_URL, get_url_list[i].in,
                      get_url_list[i].urlflags);
    if(!rc) {
      rc = curl_url_get(urlp, CURLUPART_URL, &url, get_url_list[i].getflags);

      if(rc) {
        fprintf(stderr, "%s:%d returned %d\n",
                __FILE__, __LINE__, (int)rc);
        error++;
      }
      else {
        if(checkurl(url, get_url_list[i].out)) {
          error++;
        }
      }
    }
    else if(rc != get_url_list[i].ucode) {
      fprintf(stderr, "Get URL\nin: %s\nreturned %d (expected %d)\n",
              get_url_list[i].in, (int)rc, get_url_list[i].ucode);
      error++;
    }
    curl_free(url);
    curl_url_cleanup(urlp);
  }
  return error;
}