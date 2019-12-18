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
typedef  void* var ;
struct List {void* head; } ;

/* Variables and functions */
 void** List_Next (struct List*,void*) ; 

__attribute__((used)) static void List_Mark(var self, var gc, void(*f)(var,void*)) {
  struct List* l = self;
  var item = l->head;
  while (item) {
    f(gc, item);
    item = *List_Next(l, item);
  }
}