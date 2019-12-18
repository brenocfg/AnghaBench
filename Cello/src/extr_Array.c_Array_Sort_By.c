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
 scalar_t__ Array_Len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Array_Sort_Part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 

__attribute__((used)) static void Array_Sort_By(var self, bool(*f)(var,var)) {
  Array_Sort_Part(self, 0, Array_Len(self)-1, f);
}