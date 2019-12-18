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
typedef  int uint32_t ;
struct socket {scalar_t__ last_pid; int so_flags; scalar_t__ so_policy_gencnt; int /*<<< orphan*/  last_uuid; int /*<<< orphan*/  e_uuid; } ;
struct inpcb {scalar_t__ inp_state; struct socket* inp_socket; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INPCB_STATE_DEAD ; 
 int PROC_UUID_NECP_APP_POLICY ; 
 int PROC_UUID_NO_CELLULAR ; 
 int SOF_DELEGATED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  inp_update_cellular_policy (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inp_update_necp_want_app_policy (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_io_policy_uuid ; 
 int proc_uuid_policy_lookup (int /*<<< orphan*/ ,int*,scalar_t__*) ; 

int
inp_update_policy(struct inpcb *inp)
{
#if CONFIG_PROC_UUID_POLICY
	struct socket *so = inp->inp_socket;
	uint32_t pflags = 0;
	int32_t ogencnt;
	int err = 0;

	if (!net_io_policy_uuid ||
	    so == NULL || inp->inp_state == INPCB_STATE_DEAD)
		return (0);

	/*
	 * Kernel-created sockets that aren't delegating other sockets
	 * are currently exempted from UUID policy checks.
	 */
	if (so->last_pid == 0 && !(so->so_flags & SOF_DELEGATED))
		return (0);

	ogencnt = so->so_policy_gencnt;
	err = proc_uuid_policy_lookup(((so->so_flags & SOF_DELEGATED) ?
	    so->e_uuid : so->last_uuid), &pflags, &so->so_policy_gencnt);

	/*
	 * Discard cached generation count if the entry is gone (ENOENT),
	 * so that we go thru the checks below.
	 */
	if (err == ENOENT && ogencnt != 0)
		so->so_policy_gencnt = 0;

	/*
	 * If the generation count has changed, inspect the policy flags
	 * and act accordingly.  If a policy flag was previously set and
	 * the UUID is no longer present in the table (ENOENT), treat it
	 * as if the flag has been cleared.
	 */
	if ((err == 0 || err == ENOENT) && ogencnt != so->so_policy_gencnt) {
		/* update cellular policy for this socket */
		if (err == 0 && (pflags & PROC_UUID_NO_CELLULAR)) {
			inp_update_cellular_policy(inp, TRUE);
		} else if (!(pflags & PROC_UUID_NO_CELLULAR)) {
			inp_update_cellular_policy(inp, FALSE);
		}
#if NECP
		/* update necp want app policy for this socket */
		if (err == 0 && (pflags & PROC_UUID_NECP_APP_POLICY)) {
			inp_update_necp_want_app_policy(inp, TRUE);
		} else if (!(pflags & PROC_UUID_NECP_APP_POLICY)) {
			inp_update_necp_want_app_policy(inp, FALSE);
		}
#endif /* NECP */
	}

	return ((err == ENOENT) ? 0 : err);
#else /* !CONFIG_PROC_UUID_POLICY */
#pragma unused(inp)
	return (0);
#endif /* !CONFIG_PROC_UUID_POLICY */
}