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
struct jme_adapter {int /*<<< orphan*/  rxempty_task; int /*<<< orphan*/  rxclean_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  link_changing; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_POLL ; 
 int /*<<< orphan*/  JME_NAPI_DISABLE (struct jme_adapter*) ; 
 int /*<<< orphan*/  PCC_OFF ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_set_rx_pcc (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void jme_pause_rx(struct jme_adapter *jme)
{
	atomic_dec(&jme->link_changing);

	jme_set_rx_pcc(jme, PCC_OFF);
	if (test_bit(JME_FLAG_POLL, &jme->flags)) {
		JME_NAPI_DISABLE(jme);
	} else {
		tasklet_disable(&jme->rxclean_task);
		tasklet_disable(&jme->rxempty_task);
	}
}