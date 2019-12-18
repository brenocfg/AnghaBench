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
struct dynpcc_info {scalar_t__ cnt; void* attempt; void* cur; } ;
struct jme_adapter {int /*<<< orphan*/  link_changing; int /*<<< orphan*/  rxempty_task; int /*<<< orphan*/  rxclean_task; int /*<<< orphan*/  flags; struct dynpcc_info dpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_POLL ; 
 int /*<<< orphan*/  JME_NAPI_ENABLE (struct jme_adapter*) ; 
 void* PCC_P1 ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_set_rx_pcc (struct jme_adapter*,void*) ; 
 int /*<<< orphan*/  tasklet_hi_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void jme_resume_rx(struct jme_adapter *jme)
{
	struct dynpcc_info *dpi = &(jme->dpi);

	if (test_bit(JME_FLAG_POLL, &jme->flags)) {
		JME_NAPI_ENABLE(jme);
	} else {
		tasklet_hi_enable(&jme->rxclean_task);
		tasklet_hi_enable(&jme->rxempty_task);
	}
	dpi->cur		= PCC_P1;
	dpi->attempt		= PCC_P1;
	dpi->cnt		= 0;
	jme_set_rx_pcc(jme, PCC_P1);

	atomic_inc(&jme->link_changing);
}