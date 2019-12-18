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
typedef  scalar_t__ var ;

/* Variables and functions */
 scalar_t__ Slice_Iter_Init (scalar_t__) ; 
 scalar_t__ Slice_Iter_Next (scalar_t__,scalar_t__) ; 
 scalar_t__ eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool Slice_Mem(var self, var key) {
  var curr = Slice_Iter_Init(self);
  while (curr) {
    if (eq(curr, key)) { return true; }
    curr = Slice_Iter_Next(self, curr);
  }
  return false;
}