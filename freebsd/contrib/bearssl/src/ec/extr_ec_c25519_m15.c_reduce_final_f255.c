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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCOPY (int,int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static uint32_t
reduce_final_f255(uint32_t *d)
{
	uint32_t t[20];
	uint32_t cc;
	int i;

	memcpy(t, d, sizeof t);
	cc = 19;
	for (i = 0; i < 20; i ++) {
		uint32_t w;

		w = t[i] + cc;
		cc = w >> 13;
		t[i] = w & 0x1FFF;
	}
	cc = t[19] >> 8;
	t[19] &= 0xFF;
	CCOPY(cc, d, t, sizeof t);
	return cc;
}