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
typedef  char u8 ;

/* Variables and functions */

__attribute__((used)) static int ldm_parse_hexbyte (const u8 *src)
{
	unsigned int x;		/* For correct wrapping */
	int h;

	/* high part */
	if      ((x = src[0] - '0') <= '9'-'0') h = x;
	else if ((x = src[0] - 'a') <= 'f'-'a') h = x+10;
	else if ((x = src[0] - 'A') <= 'F'-'A') h = x+10;
	else return -1;
	h <<= 4;

	/* low part */
	if ((x = src[1] - '0') <= '9'-'0') return h | x;
	if ((x = src[1] - 'a') <= 'f'-'a') return h | (x+10);
	if ((x = src[1] - 'A') <= 'F'-'A') return h | (x+10);
	return -1;
}