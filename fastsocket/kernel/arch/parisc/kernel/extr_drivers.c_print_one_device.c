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
struct parisc_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ check_dev (struct device*) ; 
 int /*<<< orphan*/  print_parisc_device (struct parisc_device*) ; 
 struct parisc_device* to_parisc_device (struct device*) ; 

__attribute__((used)) static int print_one_device(struct device * dev, void * data)
{
	struct parisc_device * pdev = to_parisc_device(dev);

	if (check_dev(dev))
		print_parisc_device(pdev);
	return 0;
}