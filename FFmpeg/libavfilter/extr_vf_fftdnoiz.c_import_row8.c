#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ im; int /*<<< orphan*/  re; } ;
typedef  TYPE_1__ FFTComplex ;

/* Variables and functions */

__attribute__((used)) static void import_row8(FFTComplex *dst, uint8_t *src, int rw)
{
    int j;

    for (j = 0; j < rw; j++) {
        dst[j].re = src[j];
        dst[j].im = 0;
    }
}