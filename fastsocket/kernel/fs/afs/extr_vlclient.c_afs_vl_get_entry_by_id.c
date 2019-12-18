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
struct key {int dummy; } ;
struct in_addr {int dummy; } ;
struct afs_wait_mode {int dummy; } ;
struct afs_call {void** request; int /*<<< orphan*/  port; int /*<<< orphan*/  service_id; struct afs_cache_vlocation* reply; struct key* key; } ;
struct afs_cache_vlocation {int dummy; } ;
typedef  int /*<<< orphan*/  afs_voltype_t ;
typedef  int /*<<< orphan*/  afs_volid_t ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VL_PORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VLGETENTRYBYID ; 
 int /*<<< orphan*/  VL_SERVICE ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXVLGetEntryById ; 
 struct afs_call* afs_alloc_flat_call (int /*<<< orphan*/ *,int,int) ; 
 int afs_make_call (struct in_addr*,struct afs_call*,int /*<<< orphan*/ ,struct afs_wait_mode const*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

int afs_vl_get_entry_by_id(struct in_addr *addr,
			   struct key *key,
			   afs_volid_t volid,
			   afs_voltype_t voltype,
			   struct afs_cache_vlocation *entry,
			   const struct afs_wait_mode *wait_mode)
{
	struct afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(&afs_RXVLGetEntryById, 12, 384);
	if (!call)
		return -ENOMEM;

	call->key = key;
	call->reply = entry;
	call->service_id = VL_SERVICE;
	call->port = htons(AFS_VL_PORT);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETENTRYBYID);
	*bp++ = htonl(volid);
	*bp   = htonl(voltype);

	/* initiate the call */
	return afs_make_call(addr, call, GFP_KERNEL, wait_mode);
}