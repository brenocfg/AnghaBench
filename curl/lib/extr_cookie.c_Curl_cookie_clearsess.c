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
struct CookieInfo {struct Cookie** cookies; int /*<<< orphan*/  numcookies; } ;
struct Cookie {struct Cookie* next; int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 unsigned int COOKIE_HASH_SIZE ; 
 int /*<<< orphan*/  freecookie (struct Cookie*) ; 

void Curl_cookie_clearsess(struct CookieInfo *cookies)
{
  struct Cookie *first, *curr, *next, *prev = NULL;
  unsigned int i;

  if(!cookies)
    return;

  for(i = 0; i < COOKIE_HASH_SIZE; i++) {
    if(!cookies->cookies[i])
      continue;

    first = curr = prev = cookies->cookies[i];

    for(; curr; curr = next) {
      next = curr->next;
      if(!curr->expires) {
        if(first == curr)
          first = next;

        if(prev == curr)
          prev = next;
        else
          prev->next = next;

        freecookie(curr);
        cookies->numcookies--;
      }
      else
        prev = curr;
    }

    cookies->cookies[i] = first;
  }
}