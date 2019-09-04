#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ CURLUcode ;
typedef  int /*<<< orphan*/  CURLU ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUPART_HOST ; 
 int /*<<< orphan*/  CURLUPART_PATH ; 
 int /*<<< orphan*/  CURLUPART_URL ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 int /*<<< orphan*/ * curl_url () ; 
 int /*<<< orphan*/  curl_url_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_url_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int main(void)
{
  CURLU *h;
  CURLUcode uc;
  char *host;
  char *path;

  h = curl_url(); /* get a handle to work with */
  if(!h)
    return 1;

  /* parse a full URL */
  uc = curl_url_set(h, CURLUPART_URL, "http://example.com/path/index.html", 0);
  if(uc)
    goto fail;

  /* extract host name from the parsed URL */
  uc = curl_url_get(h, CURLUPART_HOST, &host, 0);
  if(!uc) {
    printf("Host name: %s\n", host);
    curl_free(host);
  }

  /* extract the path from the parsed URL */
  uc = curl_url_get(h, CURLUPART_PATH, &path, 0);
  if(!uc) {
    printf("Path: %s\n", path);
    curl_free(path);
  }

  /* redirect with a relative URL */
  uc = curl_url_set(h, CURLUPART_URL, "../another/second.html", 0);
  if(uc)
    goto fail;

  /* extract the new, updated path */
  uc = curl_url_get(h, CURLUPART_PATH, &path, 0);
  if(!uc) {
    printf("Path: %s\n", path);
    curl_free(path);
  }

  fail:
  curl_url_cleanup(h); /* free url handle */
  return 0;
}