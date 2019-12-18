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
struct nvidia_par {int /*<<< orphan*/  pci_dev; } ;
struct fb_info {int* bl_curve; } ;

/* Variables and functions */
 int LEVEL_STEP ; 
 int MAX_LEVEL ; 
 int MIN_LEVEL ; 
 struct fb_info* pci_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvidia_bl_get_level_brightness(struct nvidia_par *par,
		int level)
{
	struct fb_info *info = pci_get_drvdata(par->pci_dev);
	int nlevel;

	/* Get and convert the value */
	/* No locking of bl_curve since we read a single value */
	nlevel = MIN_LEVEL + info->bl_curve[level] * LEVEL_STEP;

	if (nlevel < 0)
		nlevel = 0;
	else if (nlevel < MIN_LEVEL)
		nlevel = MIN_LEVEL;
	else if (nlevel > MAX_LEVEL)
		nlevel = MAX_LEVEL;

	return nlevel;
}