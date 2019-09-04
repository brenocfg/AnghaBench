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
struct curl_llist_element {struct curl_llist_element* next; struct curl_llist_element* prev; } ;
struct curl_llist {scalar_t__ size; struct curl_llist_element* tail; struct curl_llist_element* head; } ;

/* Variables and functions */

void Curl_llist_move(struct curl_llist *list, struct curl_llist_element *e,
                     struct curl_llist *to_list,
                     struct curl_llist_element *to_e)
{
  /* Remove element from list */
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
    e->prev->next = e->next;
    if(!e->next)
      list->tail = e->prev;
    else
      e->next->prev = e->prev;
  }

  --list->size;

  /* Add element to to_list after to_e */
  if(to_list->size == 0) {
    to_list->head = e;
    to_list->head->prev = NULL;
    to_list->head->next = NULL;
    to_list->tail = e;
  }
  else {
    e->next = to_e->next;
    e->prev = to_e;
    if(to_e->next) {
      to_e->next->prev = e;
    }
    else {
      to_list->tail = e;
    }
    to_e->next = e;
  }

  ++to_list->size;
}