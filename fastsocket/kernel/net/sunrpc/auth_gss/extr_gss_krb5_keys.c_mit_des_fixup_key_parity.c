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

/* Variables and functions */
 int parity_char (int) ; 

__attribute__((used)) static void mit_des_fixup_key_parity(u8 key[8])
{
	int i;
	for (i = 0; i < 8; i++) {
		key[i] &= 0xfe;
		key[i] |= 1^parity_char(key[i]);
	}
}