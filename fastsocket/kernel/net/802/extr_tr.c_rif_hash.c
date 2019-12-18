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
 int RIF_TABLE_SIZE ; 

__attribute__((used)) static inline unsigned long rif_hash(const unsigned char *addr)
{
	unsigned long x;

	x = addr[0];
	x = (x << 2) ^ addr[1];
	x = (x << 2) ^ addr[2];
	x = (x << 2) ^ addr[3];
	x = (x << 2) ^ addr[4];
	x = (x << 2) ^ addr[5];

	x ^= x >> 8;

	return x & (RIF_TABLE_SIZE - 1);
}