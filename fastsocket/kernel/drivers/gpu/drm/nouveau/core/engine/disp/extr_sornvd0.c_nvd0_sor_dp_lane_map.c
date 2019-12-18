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
typedef  int u8 ;
typedef  int const u32 ;
struct nv50_disp_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u32
nvd0_sor_dp_lane_map(struct nv50_disp_priv *priv, u8 lane)
{
	static const u8 nvd0[] = { 16, 8, 0, 24 };
	return nvd0[lane];
}