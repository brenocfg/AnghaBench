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
struct rt2x00_dev {int dummy; } ;
struct link_qual {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2400pci_set_vgc (struct rt2x00_dev*,struct link_qual*,int) ; 

__attribute__((used)) static void rt2400pci_reset_tuner(struct rt2x00_dev *rt2x00dev,
				  struct link_qual *qual)
{
	rt2400pci_set_vgc(rt2x00dev, qual, 0x08);
}