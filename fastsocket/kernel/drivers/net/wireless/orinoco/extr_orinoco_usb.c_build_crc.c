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
typedef  int u8 ;
typedef  int u16 ;
struct ezusb_packet {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 build_crc(struct ezusb_packet *data)
{
	u16 crc = 0;
	u8 *bytes = (u8 *)data;
	int i;

	for (i = 0; i < 8; i++)
		crc = (crc << 1) + bytes[i];

	return crc;
}