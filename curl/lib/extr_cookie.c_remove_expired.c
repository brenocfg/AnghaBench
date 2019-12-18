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
struct CookieInfo {int /*<<< orphan*/  numcookies; struct Cookie** cookies; } ;
struct Cookie {scalar_t__ expires; struct Cookie* next; } ;
typedef  scalar_t__ curl_off_t ;

/* Variables and functions */
 unsigned int COOKIE_HASH_SIZE ; 
 int /*<<< orphan*/  freecookie (struct Cookie*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_expired(struct CookieInfo *cookies)
{
  struct Cookie *co, *nx;
  curl_off_t now = (curl_off_t)time(NULL);
  unsigned int i;

  for(i = 0; i < COOKIE_HASH_SIZE; i++) {
    struct Cookie *pv = NULL;
    co = cookies->cookies[i];
    while(co) {
      nx = co->next;
      if(co->expires && co->expires < now) {
        if(!pv) {
          cookies->cookies[i] = co->next;
        }
        else {
          pv->next = co->next;
        }
        cookies->numcookies--;
        freecookie(co);
      }
      else {
        pv = co;
      }
      co = nx;
    }
  }
}