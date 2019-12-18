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
struct enclosure_device {int dummy; } ;
struct enclosure_component {int locate; } ;

/* Variables and functions */
 unsigned char* ses_get_page2_descriptor (struct enclosure_device*,struct enclosure_component*) ; 

__attribute__((used)) static void ses_get_locate(struct enclosure_device *edev,
			   struct enclosure_component *ecomp)
{
	unsigned char *desc;

	desc = ses_get_page2_descriptor(edev, ecomp);
	if (desc)
		ecomp->locate = (desc[2] & 0x02) ? 1 : 0;
}