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
typedef  int* uuid_t ;
typedef  int uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_node (int*) ; 
 int /*<<< orphan*/  read_random (int*,int) ; 
 int read_time () ; 

void
uuid_generate_time(uuid_t out)
{
	uint64_t time;

	read_node(&out[10]);
	read_random(&out[8], 2);

	time = read_time();
	out[0] = (uint8_t)(time >> 24);
	out[1] = (uint8_t)(time >> 16);
	out[2] = (uint8_t)(time >> 8);
	out[3] = (uint8_t)time;
	out[4] = (uint8_t)(time >> 40);
	out[5] = (uint8_t)(time >> 32);
	out[6] = (uint8_t)(time >> 56);
	out[7] = (uint8_t)(time >> 48);
 
	out[6] = (out[6] & 0x0F) | 0x10;
	out[8] = (out[8] & 0x3F) | 0x80;
}