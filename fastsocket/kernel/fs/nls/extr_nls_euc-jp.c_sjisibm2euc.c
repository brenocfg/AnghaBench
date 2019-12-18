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

/* Variables and functions */
 scalar_t__ IS_EUC_IBM2JISX0208 (unsigned char,unsigned char) ; 
 unsigned char SS3 ; 
 unsigned char** sjisibm2euc_map ; 

__attribute__((used)) static inline int sjisibm2euc(unsigned char *euc, const unsigned char sjis_hi,
			      const unsigned char sjis_lo)
{
	int index;

	index = ((sjis_hi - 0xFA) * (0xFD - 0x40)) + (sjis_lo - 0x40);
	if (IS_EUC_IBM2JISX0208(sjisibm2euc_map[index][0],
				sjisibm2euc_map[index][1])) {
		euc[0] = sjisibm2euc_map[index][0];
		euc[1] = sjisibm2euc_map[index][1];
		return 2;
	} else {
		euc[0] = SS3;
		euc[1] = sjisibm2euc_map[index][0];
		euc[2] = sjisibm2euc_map[index][1];
		return 3;
	}
}