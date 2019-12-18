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
struct dquot {int /*<<< orphan*/  dq_type; int /*<<< orphan*/  dq_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqi_priv; } ;

/* Variables and functions */
 int qtree_write_dquot (int /*<<< orphan*/ ,struct dquot*) ; 
 TYPE_1__* sb_dqinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v2_write_dquot(struct dquot *dquot)
{
	return qtree_write_dquot(sb_dqinfo(dquot->dq_sb, dquot->dq_type)->dqi_priv, dquot);
}