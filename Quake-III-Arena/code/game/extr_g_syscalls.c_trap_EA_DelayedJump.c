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
 int /*<<< orphan*/  BOTLIB_EA_DELAYED_JUMP ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int) ; 

void trap_EA_DelayedJump(int client) {
	syscall( BOTLIB_EA_DELAYED_JUMP, client );
}