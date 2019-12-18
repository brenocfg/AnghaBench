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
struct ivtv {int /*<<< orphan*/ * enc_mem; int /*<<< orphan*/ * dec_mem; scalar_t__ has_cx23415; int /*<<< orphan*/ * reg_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivtv_iounmap(struct ivtv *itv)
{
	if (itv == NULL)
		return;

	/* Release registers memory */
	if (itv->reg_mem != NULL) {
		IVTV_DEBUG_INFO("releasing reg_mem\n");
		iounmap(itv->reg_mem);
		itv->reg_mem = NULL;
	}
	/* Release io memory */
	if (itv->has_cx23415 && itv->dec_mem != NULL) {
		IVTV_DEBUG_INFO("releasing dec_mem\n");
		iounmap(itv->dec_mem);
	}
	itv->dec_mem = NULL;

	/* Release io memory */
	if (itv->enc_mem != NULL) {
		IVTV_DEBUG_INFO("releasing enc_mem\n");
		iounmap(itv->enc_mem);
		itv->enc_mem = NULL;
	}
}