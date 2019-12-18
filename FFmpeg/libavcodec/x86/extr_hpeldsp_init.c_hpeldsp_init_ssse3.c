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
struct TYPE_3__ {int /*<<< orphan*/ ** avg_pixels_tab; int /*<<< orphan*/ ** put_pixels_tab; } ;
typedef  TYPE_1__ HpelDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_avg_pixels16_xy2_ssse3 ; 
 int /*<<< orphan*/  ff_avg_pixels8_xy2_ssse3 ; 
 int /*<<< orphan*/  ff_put_pixels16_xy2_ssse3 ; 
 int /*<<< orphan*/  ff_put_pixels8_xy2_ssse3 ; 

__attribute__((used)) static void hpeldsp_init_ssse3(HpelDSPContext *c, int flags)
{
#if HAVE_SSSE3_EXTERNAL
    c->put_pixels_tab[0][3]            = ff_put_pixels16_xy2_ssse3;
    c->avg_pixels_tab[0][3]            = ff_avg_pixels16_xy2_ssse3;
    c->put_pixels_tab[1][3]            = ff_put_pixels8_xy2_ssse3;
    c->avg_pixels_tab[1][3]            = ff_avg_pixels8_xy2_ssse3;
#endif
}