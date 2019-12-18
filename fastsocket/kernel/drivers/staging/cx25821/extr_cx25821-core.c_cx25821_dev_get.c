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
struct pci_dev {int dummy; } ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 struct cx25821_dev* pci_get_drvdata (struct pci_dev*) ; 

struct cx25821_dev *cx25821_dev_get(struct pci_dev *pci)
{
	struct cx25821_dev *dev = pci_get_drvdata(pci);
	return dev;
}