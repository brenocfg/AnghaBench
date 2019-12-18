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
typedef  int /*<<< orphan*/  u32 ;
struct pm2fb_par {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PM2R_RD_INDEXED_DATA ; 
 int /*<<< orphan*/  PM2R_RD_PALETTE_WRITE_ADDRESS ; 
 int /*<<< orphan*/  pm2_WR (struct pm2fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void pm2_RDAC_WR(struct pm2fb_par *p, s32 idx, u32 v)
{
	pm2_WR(p, PM2R_RD_PALETTE_WRITE_ADDRESS, idx);
	wmb();
	pm2_WR(p, PM2R_RD_INDEXED_DATA, v);
	wmb();
}