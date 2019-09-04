#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mount_t ;
struct TYPE_3__ {int mnt_kern_flag; int mnt_authcache_ttl; } ;

/* Variables and functions */
 int CACHED_RIGHT_INFINITE_TTL ; 
 int MNTK_AUTH_CACHE_TTL ; 
 int MNTK_AUTH_OPAQUE ; 

int
vfs_authcache_ttl(mount_t mp)
{
        if ( (mp->mnt_kern_flag & (MNTK_AUTH_OPAQUE | MNTK_AUTH_CACHE_TTL)) )
	        return (mp->mnt_authcache_ttl);
	else
	        return (CACHED_RIGHT_INFINITE_TTL);
}