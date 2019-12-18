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
 int NMSEDEC_BITS ; 
 int NMSEDEC_FRACBITS ; 
 int* lut_nmsedec_sig ; 
 int* lut_nmsedec_sig0 ; 

__attribute__((used)) static int getnmsedec_sig(int x, int bpno)
{
    if (bpno > NMSEDEC_FRACBITS)
        return lut_nmsedec_sig[(x >> (bpno - NMSEDEC_FRACBITS)) & ((1 << NMSEDEC_BITS) - 1)];
    return lut_nmsedec_sig0[x & ((1 << NMSEDEC_BITS) - 1)];
}