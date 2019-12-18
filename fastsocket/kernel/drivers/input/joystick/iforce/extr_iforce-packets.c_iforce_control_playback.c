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
typedef  unsigned int u16 ;
struct iforce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_CMD_PLAY ; 
 unsigned char LO (unsigned int) ; 
 int iforce_send_packet (struct iforce*,int /*<<< orphan*/ ,unsigned char*) ; 

int iforce_control_playback(struct iforce* iforce, u16 id, unsigned int value)
{
	unsigned char data[3];

	data[0] = LO(id);
	data[1] = (value > 0) ? ((value > 1) ? 0x41 : 0x01) : 0;
	data[2] = LO(value);
	return iforce_send_packet(iforce, FF_CMD_PLAY, data);
}