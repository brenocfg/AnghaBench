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

/* Variables and functions */
 int ACC_MODE (int) ; 
 int AUDIT_PERM_WRITE ; 
 int O_CREAT ; 
 int O_TRUNC ; 

__attribute__((used)) static inline int open_arg(int flags, int mask)
{
	int n = ACC_MODE(flags);
	if (flags & (O_TRUNC | O_CREAT))
		n |= AUDIT_PERM_WRITE;
	return n & mask;
}