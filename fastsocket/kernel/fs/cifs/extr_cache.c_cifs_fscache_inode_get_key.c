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
typedef  int uint16_t ;
struct cifsInodeInfo {int /*<<< orphan*/  uniqueid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t cifs_fscache_inode_get_key(const void *cookie_netfs_data,
					   void *buffer, uint16_t maxbuf)
{
	const struct cifsInodeInfo *cifsi = cookie_netfs_data;
	uint16_t keylen;

	/* use the UniqueId as the key */
	keylen = sizeof(cifsi->uniqueid);
	if (keylen > maxbuf)
		keylen = 0;
	else
		memcpy(buffer, &cifsi->uniqueid, keylen);

	return keylen;
}