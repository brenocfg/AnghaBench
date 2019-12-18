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
struct List {int /*<<< orphan*/  nitems; struct List* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  List_Free (struct List*,struct List*) ; 
 struct List** List_Next (struct List*,struct List*) ; 
 int /*<<< orphan*/  List_Unlink (struct List*,struct List*) ; 
 int /*<<< orphan*/  ValueError ; 
 int /*<<< orphan*/  destruct (struct List*) ; 
 scalar_t__ eq (struct List*,struct List*) ; 
 int /*<<< orphan*/  throw (int /*<<< orphan*/ ,char*,struct List*) ; 

__attribute__((used)) static void List_Rem(var self, var obj) {
  struct List* l = self;
  var item = l->head;
  while (item) {
    if (eq(item, obj)) {
      List_Unlink(l, item);
      destruct(item);
      List_Free(l, item);
      l->nitems--;
      return;
    }
    item = *List_Next(l, item);
  }
  
  throw(ValueError, "Object %$ not in List!", obj);
}