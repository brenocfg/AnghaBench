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
typedef  struct Array* var ;
struct Array {scalar_t__ nitems; } ;

/* Variables and functions */
 int /*<<< orphan*/  Array_Alloc (struct Array*,scalar_t__) ; 
 int /*<<< orphan*/  Array_Item (struct Array*,scalar_t__) ; 
 int /*<<< orphan*/  Array_Reserve_More (struct Array*) ; 
 int /*<<< orphan*/  assign (int /*<<< orphan*/ ,struct Array*) ; 

__attribute__((used)) static void Array_Push(var self, var obj) {
  struct Array* a = self;
  a->nitems++;
  Array_Reserve_More(a);
  Array_Alloc(a, a->nitems-1);
  assign(Array_Item(a, a->nitems-1), obj);
}