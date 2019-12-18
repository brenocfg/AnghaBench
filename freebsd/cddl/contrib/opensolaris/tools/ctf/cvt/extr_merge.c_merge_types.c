#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ md_parent; scalar_t__ md_tgt; int /*<<< orphan*/ ** md_tdtbr; int /*<<< orphan*/ * md_tdtba; int /*<<< orphan*/ ** md_iitba; } ;
typedef  TYPE_1__ merge_cb_data_t ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  TDATA_LAYOUT_HASH_SIZE ; 
 int /*<<< orphan*/  aborterr (char*) ; 
 int /*<<< orphan*/  add_iitba_cb ; 
 int /*<<< orphan*/  add_tdtba_cb ; 
 int /*<<< orphan*/  add_tdtbr_cb ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int,char*,int) ; 
 scalar_t__ hash_count (int /*<<< orphan*/ *) ; 
 int hash_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * hash_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_count (int /*<<< orphan*/ *) ; 
 int list_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  merge_type_cb ; 
 int /*<<< orphan*/  redir_mstr_fwds (TYPE_1__*) ; 
 int /*<<< orphan*/  tdesc_layoutcmp ; 
 int /*<<< orphan*/  tdesc_layouthash ; 

__attribute__((used)) static void
merge_types(hash_t *src, merge_cb_data_t *mcd)
{
	list_t *iitba = NULL;
	list_t *tdtbr = NULL;
	int iirc, tdrc;

	mcd->md_iitba = &iitba;
	mcd->md_tdtba = hash_new(TDATA_LAYOUT_HASH_SIZE, tdesc_layouthash,
	    tdesc_layoutcmp);
	mcd->md_tdtbr = &tdtbr;

	(void) hash_iter(src, merge_type_cb, mcd);

	tdrc = hash_iter(mcd->md_tdtba, add_tdtba_cb, mcd);
	debug(3, "add_tdtba_cb added %d items\n", tdrc);

	iirc = list_iter(*mcd->md_iitba, add_iitba_cb, mcd);
	debug(3, "add_iitba_cb added %d items\n", iirc);

	assert(list_count(*mcd->md_iitba) == 0 &&
	    hash_count(mcd->md_tdtba) == 0);

	tdrc = list_iter(*mcd->md_tdtbr, add_tdtbr_cb, mcd);
	debug(3, "add_tdtbr_cb added %d items\n", tdrc);

	if (list_count(*mcd->md_tdtbr) != 0)
		aborterr("Couldn't remap all nodes\n");

	/*
	 * We now have an alist of master forwards and the ids of the new master
	 * definitions for those forwards in mcd->md_fdida.  By this point,
	 * we're guaranteed that all of the master definitions referenced in
	 * fdida have been added to the master tree.  We now traverse through
	 * the master tree, redirecting all edges inbound to forwards that have
	 * definitions to those definitions.
	 */
	if (mcd->md_parent == mcd->md_tgt) {
		redir_mstr_fwds(mcd);
	}
}