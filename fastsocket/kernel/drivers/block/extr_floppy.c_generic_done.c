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

/* Variables and functions */
 int command_status ; 
 int /*<<< orphan*/ * cont ; 
 int /*<<< orphan*/  wakeup_cont ; 

__attribute__((used)) static void generic_done(int result)
{
	command_status = result;
	cont = &wakeup_cont;
}