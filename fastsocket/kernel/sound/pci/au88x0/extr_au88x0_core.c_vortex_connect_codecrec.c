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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_CODECIN (int) ; 
 int /*<<< orphan*/  vortex_connection_adb_mixin (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
vortex_connect_codecrec(vortex_t * vortex, int en, unsigned char mixin0,
			unsigned char mixin1)
{
	/*
	   Enable: 0x1, 0x1
	   Channel: 0x11, 0x11
	   ADB Source address: 0x48, 0x49
	   Destination Asp4Topology_0x9c,0x98
	 */
	vortex_connection_adb_mixin(vortex, en, 0x11, ADB_CODECIN(0), mixin0);
	vortex_connection_adb_mixin(vortex, en, 0x11, ADB_CODECIN(1), mixin1);
}