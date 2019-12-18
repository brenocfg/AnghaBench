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
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DMU_OT_ZAP_OTHER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZTEST_DIROBJ ; 
 scalar_t__ zap_create_claim (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ztest_objset_create_cb(objset_t *os, void *arg, cred_t *cr, dmu_tx_t *tx)
{
	/*
	 * Create the objects common to all ztest datasets.
	 */
	VERIFY(zap_create_claim(os, ZTEST_DIROBJ,
	    DMU_OT_ZAP_OTHER, DMU_OT_NONE, 0, tx) == 0);
}