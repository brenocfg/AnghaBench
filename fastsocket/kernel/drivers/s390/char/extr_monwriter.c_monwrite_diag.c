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
struct monwrite_hdr {int /*<<< orphan*/  datalen; int /*<<< orphan*/  mod_level; int /*<<< orphan*/  release; int /*<<< orphan*/  version; int /*<<< orphan*/  record_num; int /*<<< orphan*/  applid; } ;
struct appldata_product_id {int /*<<< orphan*/  mod_lvl; int /*<<< orphan*/  release_nr; int /*<<< orphan*/  version_nr; int /*<<< orphan*/  record_nr; int /*<<< orphan*/  prod_fn; int /*<<< orphan*/  prod_nr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int appldata_asm (struct appldata_product_id*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int monwrite_diag(struct monwrite_hdr *myhdr, char *buffer, int fcn)
{
	struct appldata_product_id id;
	int rc;

	strcpy(id.prod_nr, "LNXAPPL");
	id.prod_fn = myhdr->applid;
	id.record_nr = myhdr->record_num;
	id.version_nr = myhdr->version;
	id.release_nr = myhdr->release;
	id.mod_lvl = myhdr->mod_level;
	rc = appldata_asm(&id, fcn, (void *) buffer, myhdr->datalen);
	if (rc <= 0)
		return rc;
	pr_err("Writing monitor data failed with rc=%i\n", rc);
	if (rc == 5)
		return -EPERM;
	return -EINVAL;
}