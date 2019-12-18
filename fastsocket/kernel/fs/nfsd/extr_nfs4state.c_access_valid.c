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
typedef  int u32 ;

/* Variables and functions */
 int NFS4_SHARE_ACCESS_BOTH ; 
 int NFS4_SHARE_ACCESS_MASK ; 
 int NFS4_SHARE_ACCESS_READ ; 
 int NFS4_SHARE_PUSH_DELEG_WHEN_UNCONTENDED ; 
 int NFS4_SHARE_WANT_CANCEL ; 
 int NFS4_SHARE_WANT_MASK ; 
 int NFS4_SHARE_WHEN_MASK ; 

__attribute__((used)) static inline int access_valid(u32 x, u32 minorversion)
{
	if ((x & NFS4_SHARE_ACCESS_MASK) < NFS4_SHARE_ACCESS_READ)
		return 0;
	if ((x & NFS4_SHARE_ACCESS_MASK) > NFS4_SHARE_ACCESS_BOTH)
		return 0;
	x &= ~NFS4_SHARE_ACCESS_MASK;
	if (minorversion && x) {
		if ((x & NFS4_SHARE_WANT_MASK) > NFS4_SHARE_WANT_CANCEL)
			return 0;
		if ((x & NFS4_SHARE_WHEN_MASK) > NFS4_SHARE_PUSH_DELEG_WHEN_UNCONTENDED)
			return 0;
		x &= ~(NFS4_SHARE_WANT_MASK | NFS4_SHARE_WHEN_MASK);
	}
	if (x)
		return 0;
	return 1;
}