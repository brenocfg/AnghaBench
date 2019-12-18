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
struct dlm_rsb {int /*<<< orphan*/  res_length; int /*<<< orphan*/  res_name; int /*<<< orphan*/  res_ls; } ;

/* Variables and functions */
 int dlm_dir_nodeid (struct dlm_rsb*) ; 
 int /*<<< orphan*/  dlm_dir_remove_entry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dlm_no_directory (int /*<<< orphan*/ ) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  send_remove (struct dlm_rsb*) ; 

__attribute__((used)) static void dir_remove(struct dlm_rsb *r)
{
	int to_nodeid;

	if (dlm_no_directory(r->res_ls))
		return;

	to_nodeid = dlm_dir_nodeid(r);
	if (to_nodeid != dlm_our_nodeid())
		send_remove(r);
	else
		dlm_dir_remove_entry(r->res_ls, to_nodeid,
				     r->res_name, r->res_length);
}