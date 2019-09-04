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
typedef  int /*<<< orphan*/  fbt_probe_t ;
typedef  int /*<<< orphan*/  dev_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ddi_remove_minor_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_invop_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbt_invop ; 
 int /*<<< orphan*/ * fbt_probetab ; 
 scalar_t__ fbt_probetab_mask ; 
 int fbt_probetab_size ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
fbt_cleanup(dev_info_t *devi)
{
	dtrace_invop_remove(fbt_invop);
	ddi_remove_minor_node(devi, NULL);
	kmem_free(fbt_probetab, fbt_probetab_size * sizeof (fbt_probe_t *));
	fbt_probetab = NULL;
	fbt_probetab_mask = 0;
}