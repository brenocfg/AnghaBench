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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long SEL_INO_MASK ; 
 int SEL_VEC_MAX ; 

__attribute__((used)) static inline u32 sel_ino_to_perm(unsigned long ino)
{
	return (ino & SEL_INO_MASK) % (SEL_VEC_MAX + 1);
}