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
 int* uni_DCtab_chrom_len ; 
 int* uni_DCtab_lum_len ; 

__attribute__((used)) static inline int mpeg4_get_dc_length(int level, int n)
{
    if (n < 4)
        return uni_DCtab_lum_len[level + 256];
    else
        return uni_DCtab_chrom_len[level + 256];
}