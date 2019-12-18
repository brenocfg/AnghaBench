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
struct s3c2410_nand_mtd {int mtd_count; struct s3c2410_nand_mtd* area; int /*<<< orphan*/ * regs; int /*<<< orphan*/ * clk; struct s3c2410_nand_mtd* mtds; int /*<<< orphan*/  mtd; } ;
struct s3c2410_nand_info {int mtd_count; struct s3c2410_nand_info* area; int /*<<< orphan*/ * regs; int /*<<< orphan*/ * clk; struct s3c2410_nand_info* mtds; int /*<<< orphan*/  mtd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  allow_clk_stop (struct s3c2410_nand_mtd*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct s3c2410_nand_mtd*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,struct s3c2410_nand_mtd*) ; 
 int /*<<< orphan*/  release_resource (struct s3c2410_nand_mtd*) ; 
 int /*<<< orphan*/  s3c2410_nand_cpufreq_deregister (struct s3c2410_nand_mtd*) ; 
 struct s3c2410_nand_mtd* to_nand_info (struct platform_device*) ; 

__attribute__((used)) static int s3c24xx_nand_remove(struct platform_device *pdev)
{
	struct s3c2410_nand_info *info = to_nand_info(pdev);

	platform_set_drvdata(pdev, NULL);

	if (info == NULL)
		return 0;

	s3c2410_nand_cpufreq_deregister(info);

	/* Release all our mtds  and their partitions, then go through
	 * freeing the resources used
	 */

	if (info->mtds != NULL) {
		struct s3c2410_nand_mtd *ptr = info->mtds;
		int mtdno;

		for (mtdno = 0; mtdno < info->mtd_count; mtdno++, ptr++) {
			pr_debug("releasing mtd %d (%p)\n", mtdno, ptr);
			nand_release(&ptr->mtd);
		}

		kfree(info->mtds);
	}

	/* free the common resources */

	if (info->clk != NULL && !IS_ERR(info->clk)) {
		if (!allow_clk_stop(info))
			clk_disable(info->clk);
		clk_put(info->clk);
	}

	if (info->regs != NULL) {
		iounmap(info->regs);
		info->regs = NULL;
	}

	if (info->area != NULL) {
		release_resource(info->area);
		kfree(info->area);
		info->area = NULL;
	}

	kfree(info);

	return 0;
}