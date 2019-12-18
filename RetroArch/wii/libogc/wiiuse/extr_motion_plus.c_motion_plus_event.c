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
typedef  int ubyte ;
struct motion_plus_t {int rx; int ry; int rz; int ext; int status; } ;

/* Variables and functions */

void motion_plus_event(struct motion_plus_t* mp, ubyte* msg)
{
	mp->rx = ((msg[5] & 0xFC) << 6) | msg[2]; // Pitch
	mp->ry = ((msg[4] & 0xFC) << 6) | msg[1]; // Roll
	mp->rz = ((msg[3] & 0xFC) << 6) | msg[0]; // Yaw

	mp->ext = msg[4] & 0x1;
	mp->status = (msg[3] & 0x3) | ((msg[4] & 0x2) << 1); // roll, yaw, pitch
}