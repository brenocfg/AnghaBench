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
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_FS ; 
 int __GFP_WAIT ; 

__attribute__((used)) static inline int
kmem_shake_allow(gfp_t gfp_mask)
{
	return ((gfp_mask & __GFP_WAIT) && (gfp_mask & __GFP_FS));
}