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
struct dcssblk_dev_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DCSSBLK_PARM_LEN ; 
 int dcssblk_add_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dcssblk_devices_sem ; 
 struct dcssblk_dev_info* dcssblk_get_device_by_name (char*) ; 
 int /*<<< orphan*/  dcssblk_root_dev ; 
 char* dcssblk_segments ; 
 int /*<<< orphan*/  dcssblk_shared_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char toupper (char) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dcssblk_check_params(void)
{
	int rc, i, j, k;
	char buf[DCSSBLK_PARM_LEN + 1];
	struct dcssblk_dev_info *dev_info;

	for (i = 0; (i < DCSSBLK_PARM_LEN) && (dcssblk_segments[i] != '\0');
	     i++) {
		for (j = i; (dcssblk_segments[j] != ',')  &&
			    (dcssblk_segments[j] != '\0') &&
			    (dcssblk_segments[j] != '(')  &&
			    (j < DCSSBLK_PARM_LEN); j++)
		{
			buf[j-i] = dcssblk_segments[j];
		}
		buf[j-i] = '\0';
		rc = dcssblk_add_store(dcssblk_root_dev, NULL, buf, j-i);
		if ((rc >= 0) && (dcssblk_segments[j] == '(')) {
			for (k = 0; (buf[k] != ':') && (buf[k] != '\0'); k++)
				buf[k] = toupper(buf[k]);
			buf[k] = '\0';
			if (!strncmp(&dcssblk_segments[j], "(local)", 7)) {
				down_read(&dcssblk_devices_sem);
				dev_info = dcssblk_get_device_by_name(buf);
				up_read(&dcssblk_devices_sem);
				if (dev_info)
					dcssblk_shared_store(&dev_info->dev,
							     NULL, "0\n", 2);
			}
		}
		while ((dcssblk_segments[j] != ',') &&
		       (dcssblk_segments[j] != '\0'))
		{
			j++;
		}
		if (dcssblk_segments[j] == '\0')
			break;
		i = j;
	}
}