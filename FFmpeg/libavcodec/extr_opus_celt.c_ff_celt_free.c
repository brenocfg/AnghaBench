#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* dsp; int /*<<< orphan*/  pvq; int /*<<< orphan*/ * imdct; } ;
typedef  TYPE_1__ CeltFrame ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  ff_celt_pvq_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mdct15_uninit (int /*<<< orphan*/ *) ; 

void ff_celt_free(CeltFrame **f)
{
    CeltFrame *frm = *f;
    int i;

    if (!frm)
        return;

    for (i = 0; i < FF_ARRAY_ELEMS(frm->imdct); i++)
        ff_mdct15_uninit(&frm->imdct[i]);

    ff_celt_pvq_uninit(&frm->pvq);

    av_freep(&frm->dsp);
    av_freep(f);
}