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
typedef  unsigned int u32 ;
struct xdr_netobj {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 unsigned int LOCK_HASH_MASK ; 
 unsigned int file_hashval (struct inode*) ; 
 unsigned int opaque_hashval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
lock_ownerstr_hashval(struct inode *inode, u32 cl_id,
		struct xdr_netobj *ownername)
{
	return (file_hashval(inode) + cl_id
			+ opaque_hashval(ownername->data, ownername->len))
		& LOCK_HASH_MASK;
}