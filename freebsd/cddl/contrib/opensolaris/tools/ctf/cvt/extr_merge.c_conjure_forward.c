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
typedef  int /*<<< orphan*/  tdesc_t ;
struct TYPE_5__ {TYPE_1__* md_tgt; } ;
typedef  TYPE_2__ merge_cb_data_t ;
struct TYPE_4__ {int /*<<< orphan*/  td_fwdlist; } ;

/* Variables and functions */
 int /*<<< orphan*/ * conjure_template (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tdesc_t *
conjure_forward(tdesc_t *old, int newselfid, merge_cb_data_t *mcd)
{
	tdesc_t *new = conjure_template(old, newselfid);

	list_add(&mcd->md_tgt->td_fwdlist, new);

	return (new);
}