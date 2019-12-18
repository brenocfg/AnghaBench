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
typedef  int u32 ;

/* Variables and functions */
 int slic_crc_init ; 
 int* slic_crc_table ; 
 int /*<<< orphan*/  slic_mcast_init_crc32 () ; 

__attribute__((used)) static unsigned char slic_mcast_get_mac_hash(char *macaddr)
{
	u32 crc;
	char *p;
	int i;
	unsigned char machash = 0;

	if (!slic_crc_init) {
		slic_mcast_init_crc32();
		slic_crc_init = 1;
	}

	crc = 0xFFFFFFFF;	/* Preload shift register, per crc-32 spec */
	for (i = 0, p = macaddr; i < 6; ++p, ++i)
		crc = (crc >> 8) ^ slic_crc_table[(crc ^ *p) & 0xFF];

	/* Return bits 1-8, transposed */
	for (i = 1; i < 9; i++)
		machash |= (((crc >> i) & 1) << (8 - i));

	return machash;
}