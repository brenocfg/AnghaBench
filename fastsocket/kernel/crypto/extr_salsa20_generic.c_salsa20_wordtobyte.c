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
typedef  int /*<<< orphan*/  x ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  U32TO8_LITTLE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__ rol32 (scalar_t__,int) ; 

__attribute__((used)) static void salsa20_wordtobyte(u8 output[64], const u32 input[16])
{
	u32 x[16];
	int i;

	memcpy(x, input, sizeof(x));
	for (i = 20; i > 0; i -= 2) {
		x[ 4] ^= rol32((x[ 0] + x[12]),  7);
		x[ 8] ^= rol32((x[ 4] + x[ 0]),  9);
		x[12] ^= rol32((x[ 8] + x[ 4]), 13);
		x[ 0] ^= rol32((x[12] + x[ 8]), 18);
		x[ 9] ^= rol32((x[ 5] + x[ 1]),  7);
		x[13] ^= rol32((x[ 9] + x[ 5]),  9);
		x[ 1] ^= rol32((x[13] + x[ 9]), 13);
		x[ 5] ^= rol32((x[ 1] + x[13]), 18);
		x[14] ^= rol32((x[10] + x[ 6]),  7);
		x[ 2] ^= rol32((x[14] + x[10]),  9);
		x[ 6] ^= rol32((x[ 2] + x[14]), 13);
		x[10] ^= rol32((x[ 6] + x[ 2]), 18);
		x[ 3] ^= rol32((x[15] + x[11]),  7);
		x[ 7] ^= rol32((x[ 3] + x[15]),  9);
		x[11] ^= rol32((x[ 7] + x[ 3]), 13);
		x[15] ^= rol32((x[11] + x[ 7]), 18);
		x[ 1] ^= rol32((x[ 0] + x[ 3]),  7);
		x[ 2] ^= rol32((x[ 1] + x[ 0]),  9);
		x[ 3] ^= rol32((x[ 2] + x[ 1]), 13);
		x[ 0] ^= rol32((x[ 3] + x[ 2]), 18);
		x[ 6] ^= rol32((x[ 5] + x[ 4]),  7);
		x[ 7] ^= rol32((x[ 6] + x[ 5]),  9);
		x[ 4] ^= rol32((x[ 7] + x[ 6]), 13);
		x[ 5] ^= rol32((x[ 4] + x[ 7]), 18);
		x[11] ^= rol32((x[10] + x[ 9]),  7);
		x[ 8] ^= rol32((x[11] + x[10]),  9);
		x[ 9] ^= rol32((x[ 8] + x[11]), 13);
		x[10] ^= rol32((x[ 9] + x[ 8]), 18);
		x[12] ^= rol32((x[15] + x[14]),  7);
		x[13] ^= rol32((x[12] + x[15]),  9);
		x[14] ^= rol32((x[13] + x[12]), 13);
		x[15] ^= rol32((x[14] + x[13]), 18);
	}
	for (i = 0; i < 16; ++i)
		x[i] += input[i];
	for (i = 0; i < 16; ++i)
		U32TO8_LITTLE(output + 4 * i,x[i]);
}