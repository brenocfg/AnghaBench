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
typedef  int uint ;
typedef  int u8 ;
typedef  int u64 ;

/* Variables and functions */
 int cpu_to_le64 (int) ; 
 int le64_to_cpup (int*) ; 

__attribute__((used)) static void challenge(u8 *bytes)
{
	u64 *i64P, tmp64;
	uint i, idx;

	for (idx = 0; idx < 32; ++idx) {

		if (idx & 0x3)
			bytes[(idx >> 3) + 3] = bytes[(idx >> 2) & 0x3];

		switch (idx & 0x3) {
		case 0x3:
			bytes[2] += bytes[3] * 4 + bytes[4] + bytes[5];
			bytes[4] += bytes[(idx & 0x1) * 2] * 9 + 9;
			break;
		case 0x1:
			bytes[0] *= 8;
			bytes[0] += 7*idx + 4;
			bytes[6] += bytes[3] * 3;
			break;
		case 0x0:
			bytes[3 - (idx >> 3)] = bytes[idx >> 2];
			bytes[5] += bytes[6] * 3;
			for (i = 0; i < 3; i++)
				bytes[3] *= bytes[3] + 1;
			break;
		case 0x2:
			for (i = 0; i < 3; i++)
				bytes[1] *= bytes[6] + 1;
			for (i = 0; i < 3; i++) {
				i64P = (u64 *)bytes;
				tmp64 = le64_to_cpup(i64P);
				tmp64 <<= bytes[7] & 0x0f;
				*i64P += cpu_to_le64(tmp64);
			}
			break;
		}
	}
}