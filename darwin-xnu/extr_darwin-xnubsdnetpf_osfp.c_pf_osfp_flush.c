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
struct pf_osfp_entry {int /*<<< orphan*/  fp_oses; } ;
struct pf_os_fingerprint {int /*<<< orphan*/  fp_oses; } ;

/* Variables and functions */
 struct pf_osfp_entry* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fp_entry ; 
 int /*<<< orphan*/  fp_next ; 
 int /*<<< orphan*/  pf_osfp_entry_pl ; 
 int /*<<< orphan*/  pf_osfp_list ; 
 int /*<<< orphan*/  pf_osfp_pl ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pf_osfp_entry*) ; 

void
pf_osfp_flush(void)
{
	struct pf_os_fingerprint *fp;
	struct pf_osfp_entry *entry;

	while ((fp = SLIST_FIRST(&pf_osfp_list))) {
		SLIST_REMOVE_HEAD(&pf_osfp_list, fp_next);
		while ((entry = SLIST_FIRST(&fp->fp_oses))) {
			SLIST_REMOVE_HEAD(&fp->fp_oses, fp_entry);
			pool_put(&pf_osfp_entry_pl, entry);
		}
		pool_put(&pf_osfp_pl, fp);
	}
}