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
typedef  struct List* var ;
struct List {scalar_t__ nitems; struct List* head; int /*<<< orphan*/ * tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  List_Free (struct List*,struct List*) ; 
 struct List** List_Next (struct List*,struct List*) ; 
 int /*<<< orphan*/  destruct (struct List*) ; 

__attribute__((used)) static void List_Clear(var self) {
  struct List* l = self;
  var item = l->head;
  while (item) {
    var next = *List_Next(l, item);
	  destruct(item);
    List_Free(l, item);
    item = next;
  }
  l->tail = NULL;
  l->head = NULL;
  l->nitems = 0;
}