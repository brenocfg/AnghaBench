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
struct inpcb {int dummy; } ;

/* Variables and functions */

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