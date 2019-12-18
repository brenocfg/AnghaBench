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
struct vfp_single {int sign; int exponent; int significand; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int VFP_SINGLE_LOW_BITS ; 
 int VFP_SINGLE_MANTISSA_BITS ; 

__attribute__((used)) static inline s32 vfp_single_pack(struct vfp_single *s)
{
	u32 val;
	val = (s->sign << 16) +
	      (s->exponent << VFP_SINGLE_MANTISSA_BITS) +
	      (s->significand >> VFP_SINGLE_LOW_BITS);
	return (s32)val;
}