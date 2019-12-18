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
struct Array {size_t nitems; } ;

/* Variables and functions */
 int /*<<< orphan*/  Array_Item (struct Array*,size_t) ; 
 scalar_t__ eq (int /*<<< orphan*/ ,struct Array*) ; 

__attribute__((used)) static bool Array_Mem(var self, var obj) {
  struct Array* a = self;
  for(size_t i = 0; i < a->nitems; i++) {
    if (eq(Array_Item(a, i), obj)) {
      return true;
    }
  }
  return false;
}