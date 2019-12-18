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
struct ehci_hcd {int /*<<< orphan*/  companion_ports; int /*<<< orphan*/  hcs_params; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int HCS_N_PORTS (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct ehci_hcd* hcd_to_ehci (int /*<<< orphan*/ ) ; 
 int scnprintf (char*,int,char*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t show_companion(struct device *dev,
			      struct device_attribute *attr,
			      char *buf)
{
	struct ehci_hcd		*ehci;
	int			nports, index, n;
	int			count = PAGE_SIZE;
	char			*ptr = buf;

	ehci = hcd_to_ehci(bus_to_hcd(dev_get_drvdata(dev)));
	nports = HCS_N_PORTS(ehci->hcs_params);

	for (index = 0; index < nports; ++index) {
		if (test_bit(index, &ehci->companion_ports)) {
			n = scnprintf(ptr, count, "%d\n", index + 1);
			ptr += n;
			count -= n;
		}
	}
	return ptr - buf;
}