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
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ locks_in_grace () ; 
 scalar_t__ mandatory_lock (struct inode*) ; 

__attribute__((used)) static inline int
grace_disallows_io(struct inode *inode)
{
	return locks_in_grace() && mandatory_lock(inode);
}