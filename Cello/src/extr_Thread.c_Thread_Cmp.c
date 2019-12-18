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
 scalar_t__ Thread_C_Int (int /*<<< orphan*/ ) ; 
 scalar_t__ c_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Thread_Cmp(var self, var obj) {
  return (int)(Thread_C_Int(self) - c_int(obj));
}