#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  urlbuf ;
struct TYPE_3__ {int flags; scalar_t__ result; } ;
typedef  TYPE_1__ testparams ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_FAILONERROR ; 
 int /*<<< orphan*/  CURLOPT_RANGE ; 
 int /*<<< orphan*/  CURLOPT_RESUME_FROM ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int F_CONTENTRANGE ; 
 int F_FAIL ; 
 int F_HTTP416 ; 
 int F_IGNOREBODY ; 
 int F_RESUME ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,...) ; 
 scalar_t__ hasbody ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int onetest(CURL *curl, const char *url, const testparams *p)
{
  CURLcode res;
  unsigned int replyselector;
  char urlbuf[256];

  replyselector = (p->flags & F_CONTENTRANGE)? 1: 0;
  if(p->flags & F_HTTP416)
    replyselector += 2;
  msnprintf(urlbuf, sizeof(urlbuf), "%s%04u", url, replyselector);
  test_setopt(curl, CURLOPT_URL, urlbuf);
  test_setopt(curl, CURLOPT_RESUME_FROM, (p->flags & F_RESUME)? 3: 0);
  test_setopt(curl, CURLOPT_RANGE, !(p->flags & F_RESUME)?
                                   "3-1000000": (char *) NULL);
  test_setopt(curl, CURLOPT_FAILONERROR, (p->flags & F_FAIL)? 1: 0);
  hasbody = 0;
  res = curl_easy_perform(curl);
  if(res != p->result) {
    fprintf(stderr, "bad error code (%d): resume=%s, fail=%s, http416=%s, "
                    "content-range=%s, expected=%d\n", res,
                    (p->flags & F_RESUME)? "yes": "no",
                    (p->flags & F_FAIL)? "yes": "no",
                    (p->flags & F_HTTP416)? "yes": "no",
                    (p->flags & F_CONTENTRANGE)? "yes": "no",
                    p->result);
    return 1;
  }
  if(hasbody && (p->flags & F_IGNOREBODY)) {
    fprintf(stderr, "body should be ignored and is not: resume=%s, fail=%s, "
                    "http416=%s, content-range=%s\n",
                    (p->flags & F_RESUME)? "yes": "no",
                    (p->flags & F_FAIL)? "yes": "no",
                    (p->flags & F_HTTP416)? "yes": "no",
                    (p->flags & F_CONTENTRANGE)? "yes": "no");
    return 1;
  }
  return 0;

  test_cleanup:

  return 1;
}