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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {struct pci_dev* misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_GARTAPERTURECTL ; 
 int /*<<< orphan*/  AMD64_GARTEN ; 
 int /*<<< orphan*/  AMD_NB_GART ; 
 int /*<<< orphan*/  amd_nb_has_feature (int /*<<< orphan*/ ) ; 
 int amd_nb_num () ; 
 TYPE_1__* node_to_amd_nb (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd64_cleanup(void)
{
	u32 tmp;
	int i;

	if (!amd_nb_has_feature(AMD_NB_GART))
		return;

	for (i = 0; i < amd_nb_num(); i++) {
		struct pci_dev *dev = node_to_amd_nb(i)->misc;
		/* disable gart translation */
		pci_read_config_dword(dev, AMD64_GARTAPERTURECTL, &tmp);
		tmp &= ~AMD64_GARTEN;
		pci_write_config_dword(dev, AMD64_GARTAPERTURECTL, tmp);
	}
}