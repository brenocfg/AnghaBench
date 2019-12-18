#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct us_data {unsigned int fflags; TYPE_3__* pusb_intf; TYPE_2__* pusb_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int TOLOWER (char) ; 
 unsigned int US_FL_BAD_SENSE ; 
 unsigned int US_FL_CAPACITY_HEURISTICS ; 
 unsigned int US_FL_CAPACITY_OK ; 
 unsigned int US_FL_FIX_CAPACITY ; 
 unsigned int US_FL_IGNORE_DEVICE ; 
 unsigned int US_FL_IGNORE_RESIDUE ; 
 unsigned int US_FL_MAX_SECTORS_64 ; 
 unsigned int US_FL_NOT_LOCKABLE ; 
 unsigned int US_FL_NO_WP_DETECT ; 
 unsigned int US_FL_SANE_SENSE ; 
 unsigned int US_FL_SINGLE_LUN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,unsigned int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 char* quirks ; 
 scalar_t__ simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static void adjust_quirks(struct us_data *us)
{
	char *p;
	u16 vid = le16_to_cpu(us->pusb_dev->descriptor.idVendor);
	u16 pid = le16_to_cpu(us->pusb_dev->descriptor.idProduct);
	unsigned f = 0;
	unsigned int mask = (US_FL_SANE_SENSE | US_FL_BAD_SENSE |
			US_FL_FIX_CAPACITY |
			US_FL_CAPACITY_HEURISTICS | US_FL_IGNORE_DEVICE |
			US_FL_NOT_LOCKABLE | US_FL_MAX_SECTORS_64 |
			US_FL_CAPACITY_OK | US_FL_IGNORE_RESIDUE |
			US_FL_SINGLE_LUN | US_FL_NO_WP_DETECT);

	p = quirks;
	while (*p) {
		/* Each entry consists of VID:PID:flags */
		if (vid == simple_strtoul(p, &p, 16) &&
				*p == ':' &&
				pid == simple_strtoul(p+1, &p, 16) &&
				*p == ':')
			break;

		/* Move forward to the next entry */
		while (*p) {
			if (*p++ == ',')
				break;
		}
	}
	if (!*p)	/* No match */
		return;

	/* Collect the flags */
	while (*++p && *p != ',') {
		switch (TOLOWER(*p)) {
		case 'a':
			f |= US_FL_SANE_SENSE;
			break;
		case 'b':
			f |= US_FL_BAD_SENSE;
			break;
		case 'c':
			f |= US_FL_FIX_CAPACITY;
			break;
		case 'h':
			f |= US_FL_CAPACITY_HEURISTICS;
			break;
		case 'i':
			f |= US_FL_IGNORE_DEVICE;
			break;
		case 'l':
			f |= US_FL_NOT_LOCKABLE;
			break;
		case 'm':
			f |= US_FL_MAX_SECTORS_64;
			break;
		case 'o':
			f |= US_FL_CAPACITY_OK;
			break;
		case 'r':
			f |= US_FL_IGNORE_RESIDUE;
			break;
		case 's':
			f |= US_FL_SINGLE_LUN;
			break;
		case 'w':
			f |= US_FL_NO_WP_DETECT;
			break;
		/* Ignore unrecognized flag characters */
		}
	}
	us->fflags = (us->fflags & ~mask) | f;
	dev_info(&us->pusb_intf->dev, "Quirks match for "
			"vid %04x pid %04x: %x\n",
			vid, pid, f);
}