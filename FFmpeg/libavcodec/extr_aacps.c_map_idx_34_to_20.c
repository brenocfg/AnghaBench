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
typedef  int int8_t ;

/* Variables and functions */

__attribute__((used)) static void map_idx_34_to_20(int8_t *par_mapped, const int8_t *par, int full)
{
    par_mapped[ 0] = (2*par[ 0] +   par[ 1]) / 3;
    par_mapped[ 1] = (  par[ 1] + 2*par[ 2]) / 3;
    par_mapped[ 2] = (2*par[ 3] +   par[ 4]) / 3;
    par_mapped[ 3] = (  par[ 4] + 2*par[ 5]) / 3;
    par_mapped[ 4] = (  par[ 6] +   par[ 7]) / 2;
    par_mapped[ 5] = (  par[ 8] +   par[ 9]) / 2;
    par_mapped[ 6] =    par[10];
    par_mapped[ 7] =    par[11];
    par_mapped[ 8] = (  par[12] +   par[13]) / 2;
    par_mapped[ 9] = (  par[14] +   par[15]) / 2;
    par_mapped[10] =    par[16];
    if (full) {
        par_mapped[11] =    par[17];
        par_mapped[12] =    par[18];
        par_mapped[13] =    par[19];
        par_mapped[14] = (  par[20] +   par[21]) / 2;
        par_mapped[15] = (  par[22] +   par[23]) / 2;
        par_mapped[16] = (  par[24] +   par[25]) / 2;
        par_mapped[17] = (  par[26] +   par[27]) / 2;
        par_mapped[18] = (  par[28] +   par[29] +   par[30] +   par[31]) / 4;
        par_mapped[19] = (  par[32] +   par[33]) / 2;
    }
}