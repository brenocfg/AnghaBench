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
struct List {int /*<<< orphan*/  nitems; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 struct List* List_At (struct List*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  List_Free (struct List*,struct List*) ; 
 int /*<<< orphan*/  List_Unlink (struct List*,struct List*) ; 
 int /*<<< orphan*/  c_int (struct List*) ; 
 int /*<<< orphan*/  destruct (struct List*) ; 

__attribute__((used)) static void List_Pop_At(var self, var key) {

  struct List* l = self;
  int64_t i = c_int(key);
  
  var item = List_At(l, i);
  List_Unlink(l, item);
  destruct(item);
  List_Free(l, item);
  l->nitems--;
}