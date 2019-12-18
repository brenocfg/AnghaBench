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
struct mppcb {int /*<<< orphan*/  necp_client_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  necp_client_unregister_multipath_cb (int /*<<< orphan*/ ,struct mppcb*) ; 
 int /*<<< orphan*/  uuid_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ ) ; 

void
necp_mppcb_dispose(struct mppcb *mpp)
{
	if (!uuid_is_null(mpp->necp_client_uuid)) {
		necp_client_unregister_multipath_cb(mpp->necp_client_uuid, mpp);
		uuid_clear(mpp->necp_client_uuid);
	}
}