#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vme_lm_resource {int /*<<< orphan*/  mtx; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int* TSI148_LCSR_INTC_LMC ; 
 scalar_t__ TSI148_LCSR_INTEN ; 
 int* TSI148_LCSR_INTEN_LMEN ; 
 scalar_t__ TSI148_LCSR_INTEO ; 
 int* TSI148_LCSR_INTEO_LMEO ; 
 int TSI148_LCSR_INTS_LM0S ; 
 int TSI148_LCSR_INTS_LM1S ; 
 int TSI148_LCSR_INTS_LM2S ; 
 int TSI148_LCSR_INTS_LM3S ; 
 scalar_t__ TSI148_LCSR_LMAT ; 
 int TSI148_LCSR_LMAT_EN ; 
 int ioread32be (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/ ** lm_callback ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tsi148_bridge ; 

int tsi148_lm_detach(struct vme_lm_resource *lm, int monitor)
{
	u32 lm_en, tmp;

	mutex_lock(&(lm->mtx));

	/* Disable Location Monitor and ensure previous interrupts are clear */
	lm_en = ioread32be(tsi148_bridge->base + TSI148_LCSR_INTEN);
	lm_en &= ~TSI148_LCSR_INTEN_LMEN[monitor];
	iowrite32be(lm_en, tsi148_bridge->base + TSI148_LCSR_INTEN);

	tmp = ioread32be(tsi148_bridge->base + TSI148_LCSR_INTEO);
	tmp &= ~TSI148_LCSR_INTEO_LMEO[monitor];
	iowrite32be(tmp, tsi148_bridge->base + TSI148_LCSR_INTEO);

	iowrite32be(TSI148_LCSR_INTC_LMC[monitor],
		 tsi148_bridge->base + TSI148_LCSR_INTEO);

	/* Detach callback */
	lm_callback[monitor] = NULL;

	/* If all location monitors disabled, disable global Location Monitor */
	if ((lm_en & (TSI148_LCSR_INTS_LM0S | TSI148_LCSR_INTS_LM1S |
			TSI148_LCSR_INTS_LM2S | TSI148_LCSR_INTS_LM3S)) == 0) {
		tmp = ioread32be(tsi148_bridge->base + TSI148_LCSR_LMAT);
		tmp &= ~TSI148_LCSR_LMAT_EN;
		iowrite32be(tmp, tsi148_bridge->base + TSI148_LCSR_LMAT);
	}

	mutex_unlock(&(lm->mtx));

	return 0;
}