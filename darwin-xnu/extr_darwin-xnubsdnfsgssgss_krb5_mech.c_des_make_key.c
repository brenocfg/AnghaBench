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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccdes_key_set_odd_parity (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static void
des_make_key(const uint8_t rawkey[7], uint8_t deskey[8])
{
	uint8_t val = 0;

	memcpy(deskey, rawkey, 7);
	for (int i = 0; i < 7; i++)
		val |= ((deskey[i] & 1) << (i+1));
	deskey[7] = val;
	ccdes_key_set_odd_parity(deskey, 8);
}