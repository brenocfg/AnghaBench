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
struct TYPE_2__ {int h_nodeid; } ;
struct dlm_message {int /*<<< orphan*/  m_extra; int /*<<< orphan*/  m_hash; TYPE_1__ m_header; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_dir_remove_entry (struct dlm_ls*,int,int /*<<< orphan*/ ,int) ; 
 int dlm_hash2nodeid (struct dlm_ls*,int /*<<< orphan*/ ) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,int) ; 
 int receive_extralen (struct dlm_message*) ; 

__attribute__((used)) static void receive_remove(struct dlm_ls *ls, struct dlm_message *ms)
{
	int len, dir_nodeid, from_nodeid;

	from_nodeid = ms->m_header.h_nodeid;

	len = receive_extralen(ms);

	dir_nodeid = dlm_hash2nodeid(ls, ms->m_hash);
	if (dir_nodeid != dlm_our_nodeid()) {
		log_error(ls, "remove dir entry dir_nodeid %d from %d",
			  dir_nodeid, from_nodeid);
		return;
	}

	dlm_dir_remove_entry(ls, from_nodeid, ms->m_extra, len);
}