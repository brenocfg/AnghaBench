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
typedef  scalar_t__ UINT4 ;
typedef  int /*<<< orphan*/  POINTER ;

/* Variables and functions */
 int /*<<< orphan*/  Decode (scalar_t__*,unsigned char*,int) ; 
 int /*<<< orphan*/  FF (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GG (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S11 ; 
 int /*<<< orphan*/  S12 ; 
 int /*<<< orphan*/  S13 ; 
 int /*<<< orphan*/  S14 ; 
 int /*<<< orphan*/  S21 ; 
 int /*<<< orphan*/  S22 ; 
 int /*<<< orphan*/  S23 ; 
 int /*<<< orphan*/  S24 ; 
 int /*<<< orphan*/  S31 ; 
 int /*<<< orphan*/  S32 ; 
 int /*<<< orphan*/  S33 ; 
 int /*<<< orphan*/  S34 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void MD4Transform (UINT4 state[4], unsigned char block[64])
{
	UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

	Decode (x, block, 64);

/* Round 1 */
FF (a, b, c, d, x[ 0], S11); 				/* 1 */
FF (d, a, b, c, x[ 1], S12); 				/* 2 */
FF (c, d, a, b, x[ 2], S13); 				/* 3 */
FF (b, c, d, a, x[ 3], S14); 				/* 4 */
FF (a, b, c, d, x[ 4], S11); 				/* 5 */
FF (d, a, b, c, x[ 5], S12); 				/* 6 */
FF (c, d, a, b, x[ 6], S13); 				/* 7 */
FF (b, c, d, a, x[ 7], S14); 				/* 8 */
FF (a, b, c, d, x[ 8], S11); 				/* 9 */
FF (d, a, b, c, x[ 9], S12); 				/* 10 */
FF (c, d, a, b, x[10], S13); 			/* 11 */
FF (b, c, d, a, x[11], S14); 			/* 12 */
FF (a, b, c, d, x[12], S11); 			/* 13 */
FF (d, a, b, c, x[13], S12); 			/* 14 */
FF (c, d, a, b, x[14], S13); 			/* 15 */
FF (b, c, d, a, x[15], S14); 			/* 16 */

/* Round 2 */
GG (a, b, c, d, x[ 0], S21); 			/* 17 */
GG (d, a, b, c, x[ 4], S22); 			/* 18 */
GG (c, d, a, b, x[ 8], S23); 			/* 19 */
GG (b, c, d, a, x[12], S24); 			/* 20 */
GG (a, b, c, d, x[ 1], S21); 			/* 21 */
GG (d, a, b, c, x[ 5], S22); 			/* 22 */
GG (c, d, a, b, x[ 9], S23); 			/* 23 */
GG (b, c, d, a, x[13], S24); 			/* 24 */
GG (a, b, c, d, x[ 2], S21); 			/* 25 */
GG (d, a, b, c, x[ 6], S22); 			/* 26 */
GG (c, d, a, b, x[10], S23); 			/* 27 */
GG (b, c, d, a, x[14], S24); 			/* 28 */
GG (a, b, c, d, x[ 3], S21); 			/* 29 */
GG (d, a, b, c, x[ 7], S22); 			/* 30 */
GG (c, d, a, b, x[11], S23); 			/* 31 */
GG (b, c, d, a, x[15], S24); 			/* 32 */

/* Round 3 */
HH (a, b, c, d, x[ 0], S31);				/* 33 */
HH (d, a, b, c, x[ 8], S32); 			/* 34 */
HH (c, d, a, b, x[ 4], S33); 			/* 35 */
HH (b, c, d, a, x[12], S34); 			/* 36 */
HH (a, b, c, d, x[ 2], S31); 			/* 37 */
HH (d, a, b, c, x[10], S32); 			/* 38 */
HH (c, d, a, b, x[ 6], S33); 			/* 39 */
HH (b, c, d, a, x[14], S34); 			/* 40 */
HH (a, b, c, d, x[ 1], S31); 			/* 41 */
HH (d, a, b, c, x[ 9], S32); 			/* 42 */
HH (c, d, a, b, x[ 5], S33); 			/* 43 */
HH (b, c, d, a, x[13], S34); 			/* 44 */
HH (a, b, c, d, x[ 3], S31); 			/* 45 */
HH (d, a, b, c, x[11], S32); 			/* 46 */
HH (c, d, a, b, x[ 7], S33); 			/* 47 */
HH (b, c, d, a, x[15], S34);			/* 48 */

state[0] += a;
state[1] += b;
state[2] += c;
state[3] += d;

	/* Zeroize sensitive information.*/
	memset ((POINTER)x, 0, sizeof (x));
}