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
struct device_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int BUSID_SIZE ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 size_t ENOMEM ; 
 scalar_t__ add_match_busid (char*) ; 
 scalar_t__ del_match_busid (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int strnlen (char const*,int) ; 
 int /*<<< orphan*/  usbip_udbg (char*,char*) ; 

__attribute__((used)) static ssize_t store_match_busid(struct device_driver *dev, const char *buf,
		size_t count)
{
	int len;
	char busid[BUSID_SIZE];

	if (count < 5)
		return -EINVAL;

	/* strnlen() does not include \0 */
	len = strnlen(buf + 4, BUSID_SIZE);

	/* busid needs to include \0 termination */
	if (!(len < BUSID_SIZE))
		return -EINVAL;

	strncpy(busid, buf + 4, BUSID_SIZE);


	if (!strncmp(buf, "add ", 4)) {
		if (add_match_busid(busid) < 0)
			return -ENOMEM;
		else {
			usbip_udbg("add busid %s\n", busid);
			return count;
		}
	} else if (!strncmp(buf, "del ", 4)) {
		if (del_match_busid(busid) < 0)
			return -ENODEV;
		else {
			usbip_udbg("del busid %s\n", busid);
			return count;
		}
	} else
		return -EINVAL;
}