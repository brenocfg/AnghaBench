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
 int T1_NMSEDEC_BITS ; 
 int T1_NMSEDEC_FRACBITS ; 
 short* lut_nmsedec_sig ; 
 short* lut_nmsedec_sig0 ; 

__attribute__((used)) static short t1_getnmsedec_sig(int x, int bitpos) {
	if (bitpos > T1_NMSEDEC_FRACBITS) {
		return lut_nmsedec_sig[(x >> (bitpos - T1_NMSEDEC_FRACBITS)) & ((1 << T1_NMSEDEC_BITS) - 1)];
	}
	
	return lut_nmsedec_sig0[x & ((1 << T1_NMSEDEC_BITS) - 1)];
}