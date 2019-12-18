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
typedef  int ino_t ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_GCINODE_HASH_BITS ; 
 unsigned long hash_long (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long ihash(ino_t ino, __u64 cno)
{
	return hash_long((unsigned long)((ino << 2) + cno),
			 NILFS_GCINODE_HASH_BITS);
}