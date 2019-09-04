#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ (* nstat_watcher_add ) (TYPE_4__*,TYPE_3__*) ;} ;
typedef  TYPE_2__ nstat_provider ;
struct TYPE_11__ {int /*<<< orphan*/  context; } ;
struct TYPE_13__ {int filter; TYPE_1__ hdr; int /*<<< orphan*/  provider; } ;
typedef  TYPE_3__ nstat_msg_add_all_srcs ;
struct TYPE_14__ {int /*<<< orphan*/  ncs_mtx; int /*<<< orphan*/  ncs_flags; } ;
typedef  TYPE_4__ nstat_control_state ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTSUP ; 
 int NSTAT_FILTER_SUPPRESS_SRC_ADDED ; 
 int /*<<< orphan*/  NSTAT_FLAG_SUPPORTS_UPDATES ; 
 int /*<<< orphan*/  NSTAT_PROVIDER_LAST ; 
 int /*<<< orphan*/  PRIV_NET_PRIVILEGED_NETWORK_STATISTICS ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* mbuf_data (int /*<<< orphan*/ ) ; 
 int mbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nstat_enqueue_success (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* nstat_find_provider_by_id (int /*<<< orphan*/ ) ; 
 scalar_t__ nstat_privcheck ; 
 scalar_t__ priv_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static errno_t
nstat_control_handle_add_all(
	nstat_control_state	*state,
	mbuf_t				m)
{
	errno_t	result = 0;

	// Verify the header fits in the first mbuf
	if (mbuf_len(m) < sizeof(nstat_msg_add_all_srcs))
	{
		return EINVAL;
	}

	nstat_msg_add_all_srcs	*req = mbuf_data(m);
	if (req->provider > NSTAT_PROVIDER_LAST) return ENOENT;

	nstat_provider			*provider = nstat_find_provider_by_id(req->provider);

	if (!provider) return ENOENT;
	if (provider->nstat_watcher_add == NULL) return ENOTSUP;

	if (nstat_privcheck != 0) {
		result = priv_check_cred(kauth_cred_get(),
		    PRIV_NET_PRIVILEGED_NETWORK_STATISTICS, 0);
		if (result != 0)
			return result;
	}

	lck_mtx_lock(&state->ncs_mtx);
	if (req->filter & NSTAT_FILTER_SUPPRESS_SRC_ADDED)
	{
		// Suppression of source messages implicitly requires the use of update messages
		state->ncs_flags |= NSTAT_FLAG_SUPPORTS_UPDATES;
	}
	lck_mtx_unlock(&state->ncs_mtx);

	// rdar://problem/30301300   Different providers require different synchronization
	// to ensure that a new entry does not get double counted due to being added prior
	// to all current provider entries being added.  Hence pass the provider the details
	// in the original request for this to be applied atomically

	result = provider->nstat_watcher_add(state, req);

	if (result == 0)
		nstat_enqueue_success(req->hdr.context, state, 0);

	return result;
}