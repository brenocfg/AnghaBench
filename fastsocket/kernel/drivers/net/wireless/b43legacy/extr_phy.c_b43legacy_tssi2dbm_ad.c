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

/* Variables and functions */

__attribute__((used)) static inline
s32 b43legacy_tssi2dbm_ad(s32 num, s32 den)
{
	if (num < 0)
		return num/den;
	else
		return (num+den/2)/den;
}