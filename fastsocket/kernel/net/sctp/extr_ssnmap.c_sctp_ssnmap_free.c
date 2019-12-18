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
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct sctp_ssnmap {TYPE_2__ out; TYPE_1__ in; scalar_t__ malloced; } ;

/* Variables and functions */
 int MAX_KMALLOC_SIZE ; 
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  kfree (struct sctp_ssnmap*) ; 
 int sctp_ssnmap_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssnmap ; 

void sctp_ssnmap_free(struct sctp_ssnmap *map)
{
	if (map && map->malloced) {
		int size;

		size = sctp_ssnmap_size(map->in.len, map->out.len);
		if (size <= MAX_KMALLOC_SIZE)
			kfree(map);
		else
			free_pages((unsigned long)map, get_order(size));
		SCTP_DBG_OBJCNT_DEC(ssnmap);
	}
}