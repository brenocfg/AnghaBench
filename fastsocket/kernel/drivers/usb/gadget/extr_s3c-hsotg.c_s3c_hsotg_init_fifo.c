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
struct s3c_hsotg {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C_GNPTXFSIZ ; 
 int S3C_GNPTXFSIZ_NPTxFDep (int) ; 
 int S3C_GNPTXFSIZ_NPTxFStAddr (int) ; 
 scalar_t__ S3C_GRXFSIZ ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c_hsotg_init_fifo(struct s3c_hsotg *hsotg)
{
	/* the ryu 2.6.24 release ahs
	   writel(0x1C0, hsotg->regs + S3C_GRXFSIZ);
	   writel(S3C_GNPTXFSIZ_NPTxFStAddr(0x200) |
		S3C_GNPTXFSIZ_NPTxFDep(0x1C0),
		hsotg->regs + S3C_GNPTXFSIZ);
	*/

	/* set FIFO sizes to 2048/0x1C0 */

	writel(2048, hsotg->regs + S3C_GRXFSIZ);
	writel(S3C_GNPTXFSIZ_NPTxFStAddr(2048) |
	       S3C_GNPTXFSIZ_NPTxFDep(0x1C0),
	       hsotg->regs + S3C_GNPTXFSIZ);
}