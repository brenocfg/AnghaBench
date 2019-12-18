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
typedef  int /*<<< orphan*/  uint32_t ;
struct dlm_rsb {int /*<<< orphan*/  res_waitqueue; int /*<<< orphan*/  res_convertqueue; int /*<<< orphan*/  res_grantqueue; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 struct dlm_lkb* search_remid_list (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dlm_lkb *search_remid(struct dlm_rsb *r, int nodeid,
				    uint32_t remid)
{
	struct dlm_lkb *lkb;

	lkb = search_remid_list(&r->res_grantqueue, nodeid, remid);
	if (lkb)
		return lkb;
	lkb = search_remid_list(&r->res_convertqueue, nodeid, remid);
	if (lkb)
		return lkb;
	lkb = search_remid_list(&r->res_waitqueue, nodeid, remid);
	if (lkb)
		return lkb;
	return NULL;
}