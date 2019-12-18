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
typedef  char const curl_slist ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 scalar_t__ CURLAUTH_ANY ; 
 int /*<<< orphan*/  CURLOPT_HEADER ; 
 int /*<<< orphan*/  CURLOPT_HTTPHEADER ; 
 int /*<<< orphan*/  CURLOPT_PROXY ; 
 int /*<<< orphan*/  CURLOPT_PROXYAUTH ; 
 int /*<<< orphan*/  CURLOPT_PROXYUSERPWD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 char const* PROXY ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** eh ; 
 int /*<<< orphan*/  res_easy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  res_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  res_multi_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init(int num, CURLM *cm, const char *url, const char *userpwd,
                struct curl_slist *headers)
{
  int res = 0;

  res_easy_init(eh[num]);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_URL, url);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_PROXY, PROXY);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_PROXYUSERPWD, userpwd);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_PROXYAUTH, (long)CURLAUTH_ANY);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_VERBOSE, 1L);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_HEADER, 1L);
  if(res)
    goto init_failed;

  res_easy_setopt(eh[num], CURLOPT_HTTPHEADER, headers); /* custom Host: */
  if(res)
    goto init_failed;

  res_multi_add_handle(cm, eh[num]);
  if(res)
    goto init_failed;

  return 0; /* success */

init_failed:

  curl_easy_cleanup(eh[num]);
  eh[num] = NULL;

  return res; /* failure */
}