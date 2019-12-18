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
struct TYPE_2__ {int /*<<< orphan*/ * initvals_band; int /*<<< orphan*/ * initvals; int /*<<< orphan*/ * pcm; int /*<<< orphan*/ * ucode; } ;
struct b43legacy_wldev {TYPE_1__ fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43legacy_release_firmware(struct b43legacy_wldev *dev)
{
	release_firmware(dev->fw.ucode);
	dev->fw.ucode = NULL;
	release_firmware(dev->fw.pcm);
	dev->fw.pcm = NULL;
	release_firmware(dev->fw.initvals);
	dev->fw.initvals = NULL;
	release_firmware(dev->fw.initvals_band);
	dev->fw.initvals_band = NULL;
}