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
 scalar_t__ Box_Deref (scalar_t__) ; 
 int /*<<< orphan*/  Box_Ref (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del (scalar_t__) ; 

__attribute__((used)) static void Box_Del(var self) {
  var obj = Box_Deref(self);
  if (obj) { del(obj); }
  Box_Ref(self, NULL);
}