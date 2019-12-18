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
struct curl_llist_element {struct curl_llist_element* next; TYPE_1__* prev; int /*<<< orphan*/ * ptr; } ;
struct curl_llist {scalar_t__ size; int /*<<< orphan*/  (* dtor ) (void*,void*) ;TYPE_1__* tail; struct curl_llist_element* head; } ;
struct TYPE_2__ {struct curl_llist_element* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,void*) ; 

void
Curl_llist_remove(struct curl_llist *list, struct curl_llist_element *e,
                  void *user)
{
  void *ptr;
  if(e == NULL || list->size == 0)
    return;

  if(e == list->head) {
    list->head = e->next;

    if(list->head == NULL)
      list->tail = NULL;
    else
      e->next->prev = NULL;
  }
  else {
    if(!e->prev)
      list->head = e->next;
    else
      e->prev->next = e->next;

    if(!e->next)
      list->tail = e->prev;
    else
      e->next->prev = e->prev;
  }

  ptr = e->ptr;

  e->ptr  = NULL;
  e->prev = NULL;
  e->next = NULL;

  --list->size;

  /* call the dtor() last for when it actually frees the 'e' memory itself */
  if(list->dtor)
    list->dtor(user, ptr);
}