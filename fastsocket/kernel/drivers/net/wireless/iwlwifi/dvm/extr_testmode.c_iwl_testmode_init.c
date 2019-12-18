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
struct iwl_priv {int /*<<< orphan*/  trans; int /*<<< orphan*/  tst; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_test_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tst_ops ; 

void iwl_testmode_init(struct iwl_priv *priv)
{
	iwl_test_init(&priv->tst, priv->trans, &tst_ops);
}