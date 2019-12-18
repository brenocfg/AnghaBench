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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ NFS4_SHARE_DENY_BOTH ; 

__attribute__((used)) static inline int deny_valid(u32 x)
{
	/* Note: unlike access bits, deny bits may be zero. */
	return x <= NFS4_SHARE_DENY_BOTH;
}