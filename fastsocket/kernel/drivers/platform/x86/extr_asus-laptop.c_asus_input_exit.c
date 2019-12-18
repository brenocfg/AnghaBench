#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ inputdev; } ;

/* Variables and functions */
 TYPE_1__* hotk ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 

__attribute__((used)) static void asus_input_exit(void)
{
	if (hotk->inputdev)
		input_unregister_device(hotk->inputdev);
}