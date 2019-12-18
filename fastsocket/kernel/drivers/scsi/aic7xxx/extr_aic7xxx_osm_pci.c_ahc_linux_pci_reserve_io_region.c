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
struct ahc_softc {int /*<<< orphan*/  dev_softc; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ aic7xxx_allow_memio ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int,char*) ; 

__attribute__((used)) static int
ahc_linux_pci_reserve_io_region(struct ahc_softc *ahc, resource_size_t *base)
{
	if (aic7xxx_allow_memio == 0)
		return (ENOMEM);

	*base = pci_resource_start(ahc->dev_softc, 0);
	if (*base == 0)
		return (ENOMEM);
	if (!request_region(*base, 256, "aic7xxx"))
		return (ENOMEM);
	return (0);
}