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
struct txx9aclc_soc_device {int /*<<< orphan*/  aclc_pdev; } ;
struct txx9aclc_plat_drvdata {int dummy; } ;

/* Variables and functions */
 struct txx9aclc_plat_drvdata* platform_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct txx9aclc_plat_drvdata *txx9aclc_get_plat_drvdata(
	struct txx9aclc_soc_device *sdev)
{
	return platform_get_drvdata(sdev->aclc_pdev);
}