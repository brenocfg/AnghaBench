#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int* z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ p256_jacobian ;

/* Variables and functions */
 int EQ (int,int /*<<< orphan*/ ) ; 
 int* F256 ; 
 int MUL15 (int,int) ; 
 int NEQ (unsigned char const,int) ; 
 int* P256_B ; 
 int be8_to_le13 (int*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mul_f256 (int*,int*,int*) ; 
 int /*<<< orphan*/  norm13 (int*,int*,int) ; 
 int /*<<< orphan*/  reduce_f256 (int*) ; 
 int reduce_final_f256 (int*) ; 
 int /*<<< orphan*/  square_f256 (int*,int*) ; 

__attribute__((used)) static uint32_t
p256_decode(p256_jacobian *P, const void *src, size_t len)
{
	const unsigned char *buf;
	uint32_t tx[20], ty[20], t1[20], t2[20];
	uint32_t bad;
	int i;

	if (len != 65) {
		return 0;
	}
	buf = src;

	/*
	 * First byte must be 0x04 (uncompressed format). We could support
	 * "hybrid format" (first byte is 0x06 or 0x07, and encodes the
	 * least significant bit of the Y coordinate), but it is explicitly
	 * forbidden by RFC 5480 (section 2.2).
	 */
	bad = NEQ(buf[0], 0x04);

	/*
	 * Decode the coordinates, and check that they are both lower
	 * than the modulus.
	 */
	tx[19] = be8_to_le13(tx, buf + 1, 32);
	ty[19] = be8_to_le13(ty, buf + 33, 32);
	bad |= reduce_final_f256(tx);
	bad |= reduce_final_f256(ty);

	/*
	 * Check curve equation.
	 */
	square_f256(t1, tx);
	mul_f256(t1, tx, t1);
	square_f256(t2, ty);
	for (i = 0; i < 20; i ++) {
		t1[i] += (F256[i] << 3) - MUL15(3, tx[i]) + P256_B[i] - t2[i];
	}
	norm13(t1, t1, 20);
	reduce_f256(t1);
	reduce_final_f256(t1);
	for (i = 0; i < 20; i ++) {
		bad |= t1[i];
	}

	/*
	 * Copy coordinates to the point structure.
	 */
	memcpy(P->x, tx, sizeof tx);
	memcpy(P->y, ty, sizeof ty);
	memset(P->z, 0, sizeof P->z);
	P->z[0] = 1;
	return EQ(bad, 0);
}