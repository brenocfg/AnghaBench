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
struct List {int /*<<< orphan*/  nitems; int /*<<< orphan*/  tail; } ;

/* Variables and functions */
 struct List* List_Alloc (struct List*) ; 
 int /*<<< orphan*/  List_Link (struct List*,struct List*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assign (struct List*,struct List*) ; 

__attribute__((used)) static void List_Push(var self, var obj) {
  struct List* l = self;
  var item = List_Alloc(l);
  assign(item, obj);
  List_Link(l, item, l->tail, NULL);
  l->nitems++;
}