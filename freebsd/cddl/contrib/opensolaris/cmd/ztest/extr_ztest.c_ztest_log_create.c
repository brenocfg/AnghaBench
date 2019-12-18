#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zd_zilog; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  int /*<<< orphan*/  lr_t ;
struct TYPE_9__ {int /*<<< orphan*/  lr_common; } ;
typedef  TYPE_2__ lr_create_t ;
struct TYPE_10__ {int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_3__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  TX_CREATE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* zil_itx_create (int /*<<< orphan*/ ,int) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ztest_log_create(ztest_ds_t *zd, dmu_tx_t *tx, lr_create_t *lr)
{
	char *name = (void *)(lr + 1);		/* name follows lr */
	size_t namesize = strlen(name) + 1;
	itx_t *itx;

	if (zil_replaying(zd->zd_zilog, tx))
		return;

	itx = zil_itx_create(TX_CREATE, sizeof (*lr) + namesize);
	bcopy(&lr->lr_common + 1, &itx->itx_lr + 1,
	    sizeof (*lr) + namesize - sizeof (lr_t));

	zil_itx_assign(zd->zd_zilog, itx, tx);
}