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
struct find_data {unsigned long hpa; struct parisc_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_device ; 
 int for_each_padev (int /*<<< orphan*/ ,struct find_data*) ; 

__attribute__((used)) static struct parisc_device *find_device_by_addr(unsigned long hpa)
{
	struct find_data d = {
		.hpa	= hpa,
	};
	int ret;

	ret = for_each_padev(find_device, &d);
	return ret ? d.dev : NULL;
}