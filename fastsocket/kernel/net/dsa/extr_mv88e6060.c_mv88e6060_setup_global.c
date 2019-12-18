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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GLOBAL ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mv88e6060_setup_global(struct dsa_switch *ds)
{
	/*
	 * Disable discarding of frames with excessive collisions,
	 * set the maximum frame size to 1536 bytes, and mask all
	 * interrupt sources.
	 */
	REG_WRITE(REG_GLOBAL, 0x04, 0x0800);

	/*
	 * Enable automatic address learning, set the address
	 * database size to 1024 entries, and set the default aging
	 * time to 5 minutes.
	 */
	REG_WRITE(REG_GLOBAL, 0x0a, 0x2130);

	return 0;
}