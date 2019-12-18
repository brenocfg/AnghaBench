#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 TYPE_1__ dit_stub_dai ; 
 int snd_soc_register_dai (TYPE_1__*) ; 

__attribute__((used)) static int spdif_dit_probe(struct platform_device *pdev)
{
	dit_stub_dai.dev = &pdev->dev;
	return snd_soc_register_dai(&dit_stub_dai);
}