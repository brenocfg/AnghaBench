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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct nfs_inode {TYPE_1__ fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t nfs_fscache_inode_get_key(const void *cookie_netfs_data,
					  void *buffer, uint16_t bufmax)
{
	const struct nfs_inode *nfsi = cookie_netfs_data;
	uint16_t nsize;

	/* use the inode's NFS filehandle as the key */
	nsize = nfsi->fh.size;
	memcpy(buffer, nfsi->fh.data, nsize);
	return nsize;
}