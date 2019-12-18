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
typedef  int u_int16_t ;

/* Variables and functions */
 int MAC2SFM_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int* mac2sfm ; 

__attribute__((used)) static u_int16_t
ucs_to_sfm(u_int16_t ucs_ch, int lastchar)
{
	/* The last character of filename cannot be a space or period. */
	if (lastchar) {
		if (ucs_ch == 0x20)
			return (0xf028);
		else if (ucs_ch == 0x2e)
			return (0xf029);
	}
	/* 0x01 - 0x1f is simple transformation. */
	if (ucs_ch <= 0x1f) {
		return (ucs_ch | 0xf000);
	} else /* 0x20 - 0x7f */ {
		u_int16_t lsb;

		assert((ucs_ch - 0x0020) < MAC2SFM_LEN);
		lsb = mac2sfm[ucs_ch - 0x0020];
		if (lsb != ucs_ch)
			return(0xf000 | lsb); 
	}
	return (ucs_ch);
}