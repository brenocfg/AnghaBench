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
struct proto_family_str {int dummy; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  ifnet_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct proto_family_str*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct proto_family_str*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_fam_next ; 
 int /*<<< orphan*/  proto_family_head ; 
 int /*<<< orphan*/  proto_family_mutex ; 
 struct proto_family_str* proto_plumber_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
proto_unregister_plumber(protocol_family_t protocol_family,
    ifnet_family_t interface_family)
{
	struct proto_family_str  *proto_family;

	lck_mtx_lock(proto_family_mutex);

	proto_family = proto_plumber_find(protocol_family, interface_family);
	if (proto_family == NULL) {
		lck_mtx_unlock(proto_family_mutex);
		return;
	}

	TAILQ_REMOVE(&proto_family_head, proto_family, proto_fam_next);
	FREE(proto_family, M_IFADDR);

	lck_mtx_unlock(proto_family_mutex);
}