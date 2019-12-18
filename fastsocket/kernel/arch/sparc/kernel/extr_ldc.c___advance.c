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
 unsigned long LDC_PACKET_SIZE ; 

__attribute__((used)) static unsigned long __advance(unsigned long off, unsigned long num_entries)
{
	off += LDC_PACKET_SIZE;
	if (off == (num_entries * LDC_PACKET_SIZE))
		off = 0;

	return off;
}