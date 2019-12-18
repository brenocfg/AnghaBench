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
struct uio_platdata {int /*<<< orphan*/  uioinfo; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uio_platdata*) ; 
 struct uio_platdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  uio_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uio_pdrv_remove(struct platform_device *pdev)
{
	struct uio_platdata *pdata = platform_get_drvdata(pdev);

	uio_unregister_device(pdata->uioinfo);

	kfree(pdata);

	return 0;
}