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
 int /*<<< orphan*/  Table_Resize_More (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Table_Set_Move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Table_Set(var self, var key, var val) {
  Table_Set_Move(self, key, val, false);
  Table_Resize_More(self);
}