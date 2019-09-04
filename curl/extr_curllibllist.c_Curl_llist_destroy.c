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
struct curl_llist {scalar_t__ size; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_remove (struct curl_llist*,int /*<<< orphan*/ ,void*) ; 

void
Curl_llist_destroy(struct curl_llist *list, void *user)
{
  if(list) {
    while(list->size > 0)
      Curl_llist_remove(list, list->tail, user);
  }
}