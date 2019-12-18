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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  F1 ; 
 int /*<<< orphan*/  F2 ; 
 int /*<<< orphan*/  F3 ; 
 int /*<<< orphan*/  MD4SETP (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int MD4_BLOCK_LENGTH ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void MD4Transform(u32 state[4], const u8 block[MD4_BLOCK_LENGTH])
{
	u32 a, b, c, d, in[MD4_BLOCK_LENGTH / 4];

	os_memcpy(in, block, sizeof(in));

	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];

	MD4SETP(F1, a, b, c, d, in[ 0], 3);
	MD4SETP(F1, d, a, b, c, in[ 1], 7);
	MD4SETP(F1, c, d, a, b, in[ 2], 11);
	MD4SETP(F1, b, c, d, a, in[ 3], 19);
	MD4SETP(F1, a, b, c, d, in[ 4], 3);
	MD4SETP(F1, d, a, b, c, in[ 5], 7);
	MD4SETP(F1, c, d, a, b, in[ 6], 11);
	MD4SETP(F1, b, c, d, a, in[ 7], 19);
	MD4SETP(F1, a, b, c, d, in[ 8], 3);
	MD4SETP(F1, d, a, b, c, in[ 9], 7);
	MD4SETP(F1, c, d, a, b, in[10], 11);
	MD4SETP(F1, b, c, d, a, in[11], 19);
	MD4SETP(F1, a, b, c, d, in[12], 3);
	MD4SETP(F1, d, a, b, c, in[13], 7);
	MD4SETP(F1, c, d, a, b, in[14], 11);
	MD4SETP(F1, b, c, d, a, in[15], 19);

	MD4SETP(F2, a, b, c, d, in[ 0] + 0x5a827999, 3);
	MD4SETP(F2, d, a, b, c, in[ 4] + 0x5a827999, 5);
	MD4SETP(F2, c, d, a, b, in[ 8] + 0x5a827999, 9);
	MD4SETP(F2, b, c, d, a, in[12] + 0x5a827999, 13);
	MD4SETP(F2, a, b, c, d, in[ 1] + 0x5a827999, 3);
	MD4SETP(F2, d, a, b, c, in[ 5] + 0x5a827999, 5);
	MD4SETP(F2, c, d, a, b, in[ 9] + 0x5a827999, 9);
	MD4SETP(F2, b, c, d, a, in[13] + 0x5a827999, 13);
	MD4SETP(F2, a, b, c, d, in[ 2] + 0x5a827999, 3);
	MD4SETP(F2, d, a, b, c, in[ 6] + 0x5a827999, 5);
	MD4SETP(F2, c, d, a, b, in[10] + 0x5a827999, 9);
	MD4SETP(F2, b, c, d, a, in[14] + 0x5a827999, 13);
	MD4SETP(F2, a, b, c, d, in[ 3] + 0x5a827999, 3);
	MD4SETP(F2, d, a, b, c, in[ 7] + 0x5a827999, 5);
	MD4SETP(F2, c, d, a, b, in[11] + 0x5a827999, 9);
	MD4SETP(F2, b, c, d, a, in[15] + 0x5a827999, 13);

	MD4SETP(F3, a, b, c, d, in[ 0] + 0x6ed9eba1,  3);
	MD4SETP(F3, d, a, b, c, in[ 8] + 0x6ed9eba1,  9);
	MD4SETP(F3, c, d, a, b, in[ 4] + 0x6ed9eba1, 11);
	MD4SETP(F3, b, c, d, a, in[12] + 0x6ed9eba1, 15);
	MD4SETP(F3, a, b, c, d, in[ 2] + 0x6ed9eba1,  3);
	MD4SETP(F3, d, a, b, c, in[10] + 0x6ed9eba1,  9);
	MD4SETP(F3, c, d, a, b, in[ 6] + 0x6ed9eba1, 11);
	MD4SETP(F3, b, c, d, a, in[14] + 0x6ed9eba1, 15);
	MD4SETP(F3, a, b, c, d, in[ 1] + 0x6ed9eba1,  3);
	MD4SETP(F3, d, a, b, c, in[ 9] + 0x6ed9eba1,  9);
	MD4SETP(F3, c, d, a, b, in[ 5] + 0x6ed9eba1, 11);
	MD4SETP(F3, b, c, d, a, in[13] + 0x6ed9eba1, 15);
	MD4SETP(F3, a, b, c, d, in[ 3] + 0x6ed9eba1,  3);
	MD4SETP(F3, d, a, b, c, in[11] + 0x6ed9eba1,  9);
	MD4SETP(F3, c, d, a, b, in[ 7] + 0x6ed9eba1, 11);
	MD4SETP(F3, b, c, d, a, in[15] + 0x6ed9eba1, 15);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}