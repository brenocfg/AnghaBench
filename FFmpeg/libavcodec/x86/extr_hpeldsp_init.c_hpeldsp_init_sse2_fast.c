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
struct TYPE_3__ {int /*<<< orphan*/ ** avg_pixels_tab; void*** put_pixels_tab; void*** put_no_rnd_pixels_tab; } ;
typedef  TYPE_1__ HpelDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_avg_pixels16_sse2 ; 
 int /*<<< orphan*/  ff_avg_pixels16_x2_sse2 ; 
 int /*<<< orphan*/  ff_avg_pixels16_xy2_sse2 ; 
 int /*<<< orphan*/  ff_avg_pixels16_y2_sse2 ; 
 void* ff_put_pixels16_sse2 ; 
 void* ff_put_pixels16_x2_sse2 ; 
 void* ff_put_pixels16_xy2_sse2 ; 
 void* ff_put_pixels16_y2_sse2 ; 

__attribute__((used)) static void hpeldsp_init_sse2_fast(HpelDSPContext *c, int flags)
{
#if HAVE_SSE2_EXTERNAL
    c->put_pixels_tab[0][0]        = ff_put_pixels16_sse2;
    c->put_no_rnd_pixels_tab[0][0] = ff_put_pixels16_sse2;
    c->put_pixels_tab[0][1]        = ff_put_pixels16_x2_sse2;
    c->put_pixels_tab[0][2]        = ff_put_pixels16_y2_sse2;
    c->put_pixels_tab[0][3]        = ff_put_pixels16_xy2_sse2;
    c->avg_pixels_tab[0][0]        = ff_avg_pixels16_sse2;
    c->avg_pixels_tab[0][1]        = ff_avg_pixels16_x2_sse2;
    c->avg_pixels_tab[0][2]        = ff_avg_pixels16_y2_sse2;
    c->avg_pixels_tab[0][3]        = ff_avg_pixels16_xy2_sse2;
#endif /* HAVE_SSE2_EXTERNAL */
}