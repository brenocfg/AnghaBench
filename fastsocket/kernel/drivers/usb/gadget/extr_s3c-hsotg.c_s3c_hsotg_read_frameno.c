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
struct s3c_hsotg {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C_DSTS ; 
 int S3C_DSTS_SOFFN_MASK ; 
 int S3C_DSTS_SOFFN_SHIFT ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static u32 s3c_hsotg_read_frameno(struct s3c_hsotg *hsotg)
{
	u32 dsts;

	dsts = readl(hsotg->regs + S3C_DSTS);
	dsts &= S3C_DSTS_SOFFN_MASK;
	dsts >>= S3C_DSTS_SOFFN_SHIFT;

	return dsts;
}