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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int Type_Implements_Method_At_Offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

bool type_implements_method_at_offset(var self, var cls, size_t offset) {
  return Type_Implements_Method_At_Offset(self, cls, offset);
}