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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ s0 (scalar_t__) ; 
 scalar_t__ s1 (scalar_t__) ; 

__attribute__((used)) static inline void BLEND_OP(int I, u64 *W)
{
	W[I] = s1(W[I-2]) + W[I-7] + s0(W[I-15]) + W[I-16];
}