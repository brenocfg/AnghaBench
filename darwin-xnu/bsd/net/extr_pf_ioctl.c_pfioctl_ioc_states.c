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
typedef  int user_addr_t ;
typedef  int u_long ;
typedef  int u_int32_t ;
struct proc {int dummy; } ;
struct pfsync_state {int dummy; } ;
struct pfioc_states_64 {int ps_len; int ps_buf; } ;
struct pfioc_states_32 {int ps_len; int ps_buf; } ;
struct pf_state {int /*<<< orphan*/  state_key; int /*<<< orphan*/  timeout; } ;
struct TYPE_2__ {int states; } ;

/* Variables and functions */
#define  DIOCGETSTATES 128 
 int ENOMEM ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PFTM_UNLINKED ; 
 struct pf_state* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pf_state* TAILQ_NEXT (struct pf_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FREE (struct pfsync_state*,int /*<<< orphan*/ ) ; 
 struct pfsync_state* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int copyout (struct pfsync_state*,int,int) ; 
 int /*<<< orphan*/  entry_list ; 
 int /*<<< orphan*/  pf_state_export (struct pfsync_state*,int /*<<< orphan*/ ,struct pf_state*) ; 
 TYPE_1__ pf_status ; 
 int proc_is64bit (struct proc*) ; 
 int /*<<< orphan*/  state_list ; 

__attribute__((used)) static int
pfioctl_ioc_states(u_long cmd, struct pfioc_states_32 *ps32,
    struct pfioc_states_64 *ps64, struct proc *p)
{
	int p64 = proc_is64bit(p);
	int error = 0;

	switch (cmd) {
	case DIOCGETSTATES: {		/* struct pfioc_states */
		struct pf_state		*state;
		struct pfsync_state	*pstore;
		user_addr_t		 buf;
		u_int32_t		 nr = 0;
		int			 len, size;

		len = (p64 ? ps64->ps_len : ps32->ps_len);
		if (len == 0) {
			size = sizeof (struct pfsync_state) * pf_status.states;
			if (p64)
				ps64->ps_len = size;
			else
				ps32->ps_len = size;
			break;
		}

		pstore = _MALLOC(sizeof (*pstore), M_TEMP, M_WAITOK | M_ZERO);
		if (pstore == NULL) {
			error = ENOMEM;
			break;
		}
		buf = (p64 ? ps64->ps_buf : ps32->ps_buf);

		state = TAILQ_FIRST(&state_list);
		while (state) {
			if (state->timeout != PFTM_UNLINKED) {
				if ((nr + 1) * sizeof (*pstore) > (unsigned)len)
					break;

				pf_state_export(pstore,
				    state->state_key, state);
				error = copyout(pstore, buf, sizeof (*pstore));
				if (error) {
					_FREE(pstore, M_TEMP);
					goto fail;
				}
				buf += sizeof (*pstore);
				nr++;
			}
			state = TAILQ_NEXT(state, entry_list);
		}

		size = sizeof (struct pfsync_state) * nr;
		if (p64)
			ps64->ps_len = size;
		else
			ps32->ps_len = size;

		_FREE(pstore, M_TEMP);
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}
fail:
	return (error);
}