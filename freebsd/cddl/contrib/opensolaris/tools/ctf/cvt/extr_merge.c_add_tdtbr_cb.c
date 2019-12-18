#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  t_id; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_8__ {int /*<<< orphan*/  md_tdtbr; } ;
typedef  TYPE_2__ merge_cb_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remap_node (TYPE_1__**,TYPE_1__*,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  tdesc_name (TYPE_1__*) ; 

__attribute__((used)) static int
add_tdtbr_cb(void *data, void *arg)
{
	tdesc_t **tdpp = data;
	merge_cb_data_t *mcd = arg;

	debug(3, "Remapping %s (%d)\n", tdesc_name(*tdpp), (*tdpp)->t_id);

	if (!remap_node(tdpp, *tdpp, -1, NULL, mcd))
		return (0);

	(void) list_remove(mcd->md_tdtbr, (void *)tdpp, NULL, NULL);
	return (1);
}