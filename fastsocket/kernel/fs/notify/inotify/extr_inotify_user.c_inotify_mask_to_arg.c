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
typedef  int __u32 ;

/* Variables and functions */
 int IN_ALL_EVENTS ; 
 int IN_IGNORED ; 
 int IN_ISDIR ; 
 int IN_Q_OVERFLOW ; 
 int IN_UNMOUNT ; 

__attribute__((used)) static inline u32 inotify_mask_to_arg(__u32 mask)
{
	return mask & (IN_ALL_EVENTS | IN_ISDIR | IN_UNMOUNT | IN_IGNORED |
		       IN_Q_OVERFLOW);
}