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
struct dm_target {struct dm_dev* private; } ;
struct dm_dev {char* name; } ;
typedef  int status_type_t ;

/* Variables and functions */
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,char*) ; 

__attribute__((used)) static int origin_status(struct dm_target *ti, status_type_t type, char *result,
			 unsigned int maxlen)
{
	struct dm_dev *dev = ti->private;

	switch (type) {
	case STATUSTYPE_INFO:
		result[0] = '\0';
		break;

	case STATUSTYPE_TABLE:
		snprintf(result, maxlen, "%s", dev->name);
		break;
	}

	return 0;
}