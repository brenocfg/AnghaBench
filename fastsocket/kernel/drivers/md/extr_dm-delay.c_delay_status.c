#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_target {struct delay_c* private; } ;
struct delay_c {int /*<<< orphan*/  write_delay; scalar_t__ start_write; TYPE_2__* dev_write; int /*<<< orphan*/  read_delay; scalar_t__ start_read; TYPE_1__* dev_read; int /*<<< orphan*/  writes; int /*<<< orphan*/  reads; } ;
typedef  int status_type_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,int /*<<< orphan*/ ,unsigned long long,...) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 

__attribute__((used)) static int delay_status(struct dm_target *ti, status_type_t type,
			char *result, unsigned maxlen)
{
	struct delay_c *dc = ti->private;
	int sz = 0;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%u %u", dc->reads, dc->writes);
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%s %llu %u", dc->dev_read->name,
		       (unsigned long long) dc->start_read,
		       dc->read_delay);
		if (dc->dev_write)
			DMEMIT(" %s %llu %u", dc->dev_write->name,
			       (unsigned long long) dc->start_write,
			       dc->write_delay);
		break;
	}

	return 0;
}