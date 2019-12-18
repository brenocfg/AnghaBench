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
typedef  int u16 ;

/* Variables and functions */
 int SEL_CLASS_INO_OFFSET ; 
 int SEL_VEC_MAX ; 

__attribute__((used)) static inline unsigned long sel_perm_to_ino(u16 class, u32 perm)
{
	return (class * (SEL_VEC_MAX + 1) + perm) | SEL_CLASS_INO_OFFSET;
}