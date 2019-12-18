#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  t_id; int /*<<< orphan*/  t_tdesc; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int /*<<< orphan*/  merge_cb_data_t ;

/* Variables and functions */
 TYPE_1__* conjure_template (TYPE_1__*,int) ; 
 int /*<<< orphan*/  remap_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tdesc_t *
conjure_plain(tdesc_t *old, int newselfid, merge_cb_data_t *mcd)
{
	tdesc_t *new = conjure_template(old, newselfid);

	(void) remap_node(&new->t_tdesc, old->t_tdesc, old->t_id, new, mcd);

	return (new);
}