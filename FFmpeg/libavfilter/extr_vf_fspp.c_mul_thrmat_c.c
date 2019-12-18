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

__attribute__((used)) static void mul_thrmat_c(int16_t *thr_adr_noq, int16_t *thr_adr, int q)
{
    int a;
    for (a = 0; a < 64; a++)
        thr_adr[a] = q * thr_adr_noq[a];
}