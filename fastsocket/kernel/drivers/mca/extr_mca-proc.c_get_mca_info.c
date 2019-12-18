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
struct mca_device {int dummy; } ;
typedef  int off_t ;

/* Variables and functions */
 int MCA_INTEGSCSI ; 
 int MCA_INTEGVIDEO ; 
 int MCA_MAX_SLOT_NR ; 
 int MCA_MOTHERBOARD ; 
 scalar_t__ MCA_bus ; 
 int get_mca_info_helper (struct mca_device*,char*,int) ; 
 struct mca_device* mca_find_device_by_slot (int) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int get_mca_info(char *page, char **start, off_t off,
			int count, int *eof, void *data)
{
	int i, len = 0;

	if(MCA_bus) {
		struct mca_device *mca_dev;
		/* Format POS registers of eight MCA slots */

		for(i=0; i<MCA_MAX_SLOT_NR; i++) {
			mca_dev = mca_find_device_by_slot(i);

			len += sprintf(page+len, "Slot %d: ", i+1);
			len = get_mca_info_helper(mca_dev, page, len);
		}

		/* Format POS registers of integrated video subsystem */

		mca_dev = mca_find_device_by_slot(MCA_INTEGVIDEO);
		len += sprintf(page+len, "Video : ");
		len = get_mca_info_helper(mca_dev, page, len);

		/* Format POS registers of integrated SCSI subsystem */

		mca_dev = mca_find_device_by_slot(MCA_INTEGSCSI);
		len += sprintf(page+len, "SCSI  : ");
		len = get_mca_info_helper(mca_dev, page, len);

		/* Format POS registers of motherboard */

		mca_dev = mca_find_device_by_slot(MCA_MOTHERBOARD);
		len += sprintf(page+len, "Planar: ");
		len = get_mca_info_helper(mca_dev, page, len);
	} else {
		/* Leave it empty if MCA not detected - this should *never*
		 * happen!
		 */
	}

	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
}