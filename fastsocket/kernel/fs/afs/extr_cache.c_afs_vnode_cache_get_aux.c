#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  data_version; } ;
struct TYPE_3__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; } ;
struct afs_vnode {TYPE_2__ status; TYPE_1__ fid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t afs_vnode_cache_get_aux(const void *cookie_netfs_data,
					void *buffer, uint16_t bufmax)
{
	const struct afs_vnode *vnode = cookie_netfs_data;
	uint16_t dlen;

	_enter("{%x,%x,%Lx},%p,%u",
	       vnode->fid.vnode, vnode->fid.unique, vnode->status.data_version,
	       buffer, bufmax);

	dlen = sizeof(vnode->fid.unique) + sizeof(vnode->status.data_version);
	if (dlen > bufmax)
		return 0;

	memcpy(buffer, &vnode->fid.unique, sizeof(vnode->fid.unique));
	buffer += sizeof(vnode->fid.unique);
	memcpy(buffer, &vnode->status.data_version,
	       sizeof(vnode->status.data_version));

	_leave(" = %u", dlen);
	return dlen;
}