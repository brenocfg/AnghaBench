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
struct cifs_fscache_inode_auxdata {int /*<<< orphan*/  last_change_time; int /*<<< orphan*/  last_write_time; int /*<<< orphan*/  eof; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct cifsInodeInfo {TYPE_1__ vfs_inode; int /*<<< orphan*/  server_eof; } ;
typedef  enum fscache_checkaux { ____Placeholder_fscache_checkaux } fscache_checkaux ;
typedef  int /*<<< orphan*/  auxdata ;

/* Variables and functions */
 int FSCACHE_CHECKAUX_OBSOLETE ; 
 int FSCACHE_CHECKAUX_OKAY ; 
 scalar_t__ memcmp (void const*,struct cifs_fscache_inode_auxdata*,int) ; 
 int /*<<< orphan*/  memset (struct cifs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum
fscache_checkaux cifs_fscache_inode_check_aux(void *cookie_netfs_data,
					      const void *data,
					      uint16_t datalen)
{
	struct cifs_fscache_inode_auxdata auxdata;
	struct cifsInodeInfo *cifsi = cookie_netfs_data;

	if (datalen != sizeof(auxdata))
		return FSCACHE_CHECKAUX_OBSOLETE;

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.eof = cifsi->server_eof;
	auxdata.last_write_time = cifsi->vfs_inode.i_mtime;
	auxdata.last_change_time = cifsi->vfs_inode.i_ctime;

	if (memcmp(data, &auxdata, datalen) != 0)
		return FSCACHE_CHECKAUX_OBSOLETE;

	return FSCACHE_CHECKAUX_OKAY;
}