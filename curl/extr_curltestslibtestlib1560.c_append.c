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
struct TYPE_2__ {char* in; int urlflags; char* q; int qflags; scalar_t__ ucode; int /*<<< orphan*/  out; } ;
typedef  scalar_t__ CURLUcode ;
typedef  int /*<<< orphan*/  CURLU ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUPART_QUERY ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 int CURLU_APPENDQUERY ; 
 TYPE_1__* append_list ; 
 scalar_t__ checkurl (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_url_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int append(void)
{
  int i;
  CURLUcode rc;
  CURLU *urlp;
  int error = 0;
  for(i = 0; append_list[i].in && !error; i++) {
    urlp = curl_url();
    if(!urlp) {
      error++;
      break;
    }
    rc = curl_url_set(urlp, CURLUPART_URL,
                      append_list[i].in,
                      append_list[i].urlflags);
    if(rc)
      error++;
    else
      rc = curl_url_set(urlp, CURLUPART_QUERY,
                        append_list[i].q,
                        append_list[i].qflags | CURLU_APPENDQUERY);
    if(error)
      ;
    else if(rc != append_list[i].ucode) {
      fprintf(stderr, "Append\nin: %s\nreturned %d (expected %d)\n",
              append_list[i].in, (int)rc, append_list[i].ucode);
      error++;
    }
    else if(append_list[i].ucode) {
      /* the expected error happened */
    }
    else {
      char *url;
      rc = curl_url_get(urlp, CURLUPART_URL, &url, 0);
      if(rc) {
        fprintf(stderr, "%s:%d Get URL returned %d\n",
                __FILE__, __LINE__, (int)rc);
        error++;
      }
      else {
        if(checkurl(url, append_list[i].out)) {
          error++;
        }
        curl_free(url);
      }
    }
    curl_url_cleanup(urlp);
  }
  return error;
}