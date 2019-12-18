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
struct usb_se401 {int resetlevel; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV7131_REG_ARLV ; 
 int /*<<< orphan*/  HV7131_REG_HIREFNOH ; 
 int /*<<< orphan*/  HV7131_REG_HIREFNOL ; 
 int /*<<< orphan*/  HV7131_REG_LOREFNOH ; 
 int /*<<< orphan*/  HV7131_REG_LOREFNOL ; 
 int se401_get_feature (struct usb_se401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se401_set_feature (struct usb_se401*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void se401_auto_resetlevel(struct usb_se401 *se401)
{
	unsigned int ahrc, alrc;
	int oldreset = se401->resetlevel;

	/* For some reason this normally read-only register doesn't get reset
	   to zero after reading them just once...
	 */
	se401_get_feature(se401, HV7131_REG_HIREFNOH);
	se401_get_feature(se401, HV7131_REG_HIREFNOL);
	se401_get_feature(se401, HV7131_REG_LOREFNOH);
	se401_get_feature(se401, HV7131_REG_LOREFNOL);
	ahrc = 256*se401_get_feature(se401, HV7131_REG_HIREFNOH) +
	    se401_get_feature(se401, HV7131_REG_HIREFNOL);
	alrc = 256*se401_get_feature(se401, HV7131_REG_LOREFNOH) +
	    se401_get_feature(se401, HV7131_REG_LOREFNOL);

	/* Not an exact science, but it seems to work pretty well... */
	if (alrc > 10) {
		while (alrc >= 10 && se401->resetlevel < 63) {
			se401->resetlevel++;
			alrc /= 2;
		}
	} else if (ahrc > 20) {
		while (ahrc >= 20 && se401->resetlevel > 0) {
			se401->resetlevel--;
			ahrc /= 2;
		}
	}
	if (se401->resetlevel != oldreset)
		se401_set_feature(se401, HV7131_REG_ARLV, se401->resetlevel);

	return;
}