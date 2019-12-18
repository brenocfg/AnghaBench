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
struct rt2x00_dev {int dummy; } ;
struct link_qual {int false_cca; int vgc_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2400pci_set_vgc (struct rt2x00_dev*,struct link_qual*,int) ; 

__attribute__((used)) static void rt2400pci_link_tuner(struct rt2x00_dev *rt2x00dev,
				 struct link_qual *qual, const u32 count)
{
	/*
	 * The link tuner should not run longer then 60 seconds,
	 * and should run once every 2 seconds.
	 */
	if (count > 60 || !(count & 1))
		return;

	/*
	 * Base r13 link tuning on the false cca count.
	 */
	if ((qual->false_cca > 512) && (qual->vgc_level < 0x20))
		rt2400pci_set_vgc(rt2x00dev, qual, ++qual->vgc_level);
	else if ((qual->false_cca < 100) && (qual->vgc_level > 0x08))
		rt2400pci_set_vgc(rt2x00dev, qual, --qual->vgc_level);
}