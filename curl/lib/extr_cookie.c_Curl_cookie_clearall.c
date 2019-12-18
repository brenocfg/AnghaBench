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
struct CookieInfo {scalar_t__ numcookies; int /*<<< orphan*/ ** cookies; } ;

/* Variables and functions */
 unsigned int COOKIE_HASH_SIZE ; 
 int /*<<< orphan*/  Curl_cookie_freelist (int /*<<< orphan*/ *) ; 

void Curl_cookie_clearall(struct CookieInfo *cookies)
{
  if(cookies) {
    unsigned int i;
    for(i = 0; i < COOKIE_HASH_SIZE; i++) {
      Curl_cookie_freelist(cookies->cookies[i]);
      cookies->cookies[i] = NULL;
    }
    cookies->numcookies = 0;
  }
}