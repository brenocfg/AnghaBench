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
struct List {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  List_At (struct List*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign (int /*<<< orphan*/ ,struct List*) ; 
 int /*<<< orphan*/  c_int (struct List*) ; 

__attribute__((used)) static void List_Set(var self, var key, var val) {
  struct List* l = self;
  assign(List_At(l, c_int(key)), val);
}