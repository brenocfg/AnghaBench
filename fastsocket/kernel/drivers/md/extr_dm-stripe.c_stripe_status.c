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
struct stripe_c {unsigned int stripes; TYPE_2__* stripe; scalar_t__ chunk_size; } ;
struct dm_target {scalar_t__ private; } ;
typedef  int status_type_t ;
struct TYPE_4__ {scalar_t__ physical_start; TYPE_1__* dev; int /*<<< orphan*/  error_count; } ;
struct TYPE_3__ {unsigned int name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stripe_status(struct dm_target *ti,
			 status_type_t type, char *result, unsigned int maxlen)
{
	struct stripe_c *sc = (struct stripe_c *) ti->private;
	char buffer[sc->stripes + 1];
	unsigned int sz = 0;
	unsigned int i;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%d ", sc->stripes);
		for (i = 0; i < sc->stripes; i++)  {
			DMEMIT("%s ", sc->stripe[i].dev->name);
			buffer[i] = atomic_read(&(sc->stripe[i].error_count)) ?
				'D' : 'A';
		}
		buffer[i] = '\0';
		DMEMIT("1 %s", buffer);
		break;

	case STATUSTYPE_TABLE:
		DMEMIT("%d %llu", sc->stripes,
			(unsigned long long)sc->chunk_size);
		for (i = 0; i < sc->stripes; i++)
			DMEMIT(" %s %llu", sc->stripe[i].dev->name,
			    (unsigned long long)sc->stripe[i].physical_start);
		break;
	}
	return 0;
}