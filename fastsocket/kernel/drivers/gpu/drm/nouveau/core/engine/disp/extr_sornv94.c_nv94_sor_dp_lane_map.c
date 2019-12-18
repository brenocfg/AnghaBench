#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int const u32 ;
struct nv50_disp_priv {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 TYPE_1__* nv_device (struct nv50_disp_priv*) ; 

__attribute__((used)) static inline u32
nv94_sor_dp_lane_map(struct nv50_disp_priv *priv, u8 lane)
{
	static const u8 nvaf[] = { 24, 16, 8, 0 }; /* thanks, apple.. */
	static const u8 nv94[] = { 16, 8, 0, 24 };
	if (nv_device(priv)->chipset == 0xaf)
		return nvaf[lane];
	return nv94[lane];
}