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
struct TYPE_2__ {int magic1; int magic2; char flags; char value3; char buffer1; char buffer2; char value6; char value7; char value8; } ;
struct asus_oled_packet {TYPE_1__ header; } ;
struct asus_oled_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct asus_oled_packet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_packet_header(struct asus_oled_packet *packet, char flags,
			 char value3, char buffer1, char buffer2, char value6,
			 char value7, char value8)
{
	memset(packet, 0, sizeof(struct asus_oled_header));
	packet->header.magic1 = 0x55;
	packet->header.magic2 = 0xaa;
	packet->header.flags = flags;
	packet->header.value3 = value3;
	packet->header.buffer1 = buffer1;
	packet->header.buffer2 = buffer2;
	packet->header.value6 = value6;
	packet->header.value7 = value7;
	packet->header.value8 = value8;
}