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
struct dlm_rsb {int /*<<< orphan*/  res_hash; int /*<<< orphan*/  res_length; int /*<<< orphan*/  res_name; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_message {int /*<<< orphan*/  m_hash; int /*<<< orphan*/  m_extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MSG_REMOVE ; 
 int create_message (struct dlm_rsb*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct dlm_message**,struct dlm_mhandle**) ; 
 int dlm_dir_nodeid (struct dlm_rsb*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send_message (struct dlm_mhandle*,struct dlm_message*) ; 

__attribute__((used)) static int send_remove(struct dlm_rsb *r)
{
	struct dlm_message *ms;
	struct dlm_mhandle *mh;
	int to_nodeid, error;

	to_nodeid = dlm_dir_nodeid(r);

	error = create_message(r, NULL, to_nodeid, DLM_MSG_REMOVE, &ms, &mh);
	if (error)
		goto out;

	memcpy(ms->m_extra, r->res_name, r->res_length);
	ms->m_hash = r->res_hash;

	error = send_message(mh, ms);
 out:
	return error;
}