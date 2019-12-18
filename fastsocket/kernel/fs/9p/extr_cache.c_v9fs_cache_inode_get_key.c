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
typedef  int uint16_t ;
struct v9fs_cookie {TYPE_1__* qid; int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t v9fs_cache_inode_get_key(const void *cookie_netfs_data,
					 void *buffer, uint16_t bufmax)
{
	const struct v9fs_cookie *vcookie = cookie_netfs_data;
	memcpy(buffer, &vcookie->qid->path, sizeof(vcookie->qid->path));

	P9_DPRINTK(P9_DEBUG_FSC, "inode %p get key %llu", &vcookie->inode,
		   vcookie->qid->path);
	return sizeof(vcookie->qid->path);
}