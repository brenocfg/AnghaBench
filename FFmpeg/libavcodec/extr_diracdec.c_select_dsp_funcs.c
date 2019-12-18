#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** biweight_dirac_pixels_tab; int /*<<< orphan*/ ** weight_dirac_pixels_tab; int /*<<< orphan*/ * add_dirac_obmc; int /*<<< orphan*/ * avg_dirac_pixels_tab; int /*<<< orphan*/ * put_dirac_pixels_tab; } ;
struct TYPE_5__ {int weight_log2denom; int* weight; int /*<<< orphan*/ * biweight_func; int /*<<< orphan*/ * weight_func; TYPE_1__ diracdsp; int /*<<< orphan*/  add_obmc; int /*<<< orphan*/  avg_pixels_tab; int /*<<< orphan*/  put_pixels_tab; } ;
typedef  TYPE_2__ DiracContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void select_dsp_funcs(DiracContext *s, int width, int height, int xblen, int yblen)
{
    int idx = 0;
    if (xblen > 8)
        idx = 1;
    if (xblen > 16)
        idx = 2;

    memcpy(s->put_pixels_tab, s->diracdsp.put_dirac_pixels_tab[idx], sizeof(s->put_pixels_tab));
    memcpy(s->avg_pixels_tab, s->diracdsp.avg_dirac_pixels_tab[idx], sizeof(s->avg_pixels_tab));
    s->add_obmc = s->diracdsp.add_dirac_obmc[idx];
    if (s->weight_log2denom > 1 || s->weight[0] != 1 || s->weight[1] != 1) {
        s->weight_func   = s->diracdsp.weight_dirac_pixels_tab[idx];
        s->biweight_func = s->diracdsp.biweight_dirac_pixels_tab[idx];
    } else {
        s->weight_func   = NULL;
        s->biweight_func = NULL;
    }
}