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
typedef  int s32 ;
typedef  scalar_t__ s16 ;
typedef  int fixp_t ;

/* Variables and functions */
 int FRAC_N ; 

__attribute__((used)) static inline fixp_t fixp_new16(s16 a)
{
	return ((s32)a)>>(16-FRAC_N);
}