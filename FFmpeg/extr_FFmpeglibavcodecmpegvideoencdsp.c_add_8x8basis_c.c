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
typedef  int int16_t ;

/* Variables and functions */
 int BASIS_SHIFT ; 
 int RECON_SHIFT ; 

__attribute__((used)) static void add_8x8basis_c(int16_t rem[64], int16_t basis[64], int scale)
{
    int i;

    for (i = 0; i < 8 * 8; i++)
        rem[i] += (basis[i] * scale +
                   (1 << (BASIS_SHIFT - RECON_SHIFT - 1))) >>
                  (BASIS_SHIFT - RECON_SHIFT);
}