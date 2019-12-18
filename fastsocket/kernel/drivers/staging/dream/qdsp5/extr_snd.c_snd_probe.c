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
struct snd_ctxt {struct msm_snd_endpoints* snd_epts; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct msm_snd_endpoints {int dummy; } ;

/* Variables and functions */
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_misc ; 
 struct snd_ctxt the_snd ; 

__attribute__((used)) static int snd_probe(struct platform_device *pdev)
{
	struct snd_ctxt *snd = &the_snd;
	mutex_init(&snd->lock);
	snd->snd_epts = (struct msm_snd_endpoints *)pdev->dev.platform_data;
	return misc_register(&snd_misc);
}