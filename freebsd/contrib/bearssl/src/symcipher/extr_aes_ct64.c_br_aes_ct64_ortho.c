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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
br_aes_ct64_ortho(uint64_t *q)
{
#define SWAPN(cl, ch, s, x, y)   do { \
		uint64_t a, b; \
		a = (x); \
		b = (y); \
		(x) = (a & (uint64_t)cl) | ((b & (uint64_t)cl) << (s)); \
		(y) = ((a & (uint64_t)ch) >> (s)) | (b & (uint64_t)ch); \
	} while (0)

#define SWAP2(x, y)    SWAPN(0x5555555555555555, 0xAAAAAAAAAAAAAAAA,  1, x, y)
#define SWAP4(x, y)    SWAPN(0x3333333333333333, 0xCCCCCCCCCCCCCCCC,  2, x, y)
#define SWAP8(x, y)    SWAPN(0x0F0F0F0F0F0F0F0F, 0xF0F0F0F0F0F0F0F0,  4, x, y)

	SWAP2(q[0], q[1]);
	SWAP2(q[2], q[3]);
	SWAP2(q[4], q[5]);
	SWAP2(q[6], q[7]);

	SWAP4(q[0], q[2]);
	SWAP4(q[1], q[3]);
	SWAP4(q[4], q[6]);
	SWAP4(q[5], q[7]);

	SWAP8(q[0], q[4]);
	SWAP8(q[1], q[5]);
	SWAP8(q[2], q[6]);
	SWAP8(q[3], q[7]);
}