#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct resource {int start; } ;
struct TYPE_2__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct iforce {int /*<<< orphan*/  mem_mutex; TYPE_1__ device_memory; } ;
typedef  int __u16 ;
typedef  int __s16 ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  FF_CMD_CONDITION ; 
 unsigned char HI (int) ; 
 unsigned char LO (int) ; 
 scalar_t__ allocate_resource (TYPE_1__*,struct resource*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iforce_dump_packet (char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  iforce_send_packet (struct iforce*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int make_condition_modifier(struct iforce* iforce,
	struct resource* mod_chunk, int no_alloc,
	__u16 rsat, __u16 lsat, __s16 rk, __s16 lk, u16 db, __s16 center)
{
	unsigned char data[10];

	if (!no_alloc) {
		mutex_lock(&iforce->mem_mutex);
		if (allocate_resource(&(iforce->device_memory), mod_chunk, 8,
			iforce->device_memory.start, iforce->device_memory.end, 2L,
			NULL, NULL)) {
			mutex_unlock(&iforce->mem_mutex);
			return -ENOSPC;
		}
		mutex_unlock(&iforce->mem_mutex);
	}

	data[0] = LO(mod_chunk->start);
	data[1] = HI(mod_chunk->start);

	data[2] = (100 * rk) >> 15;	/* Dangerous: the sign is extended by gcc on plateforms providing an arith shift */
	data[3] = (100 * lk) >> 15; /* This code is incorrect on cpus lacking arith shift */

	center = (500 * center) >> 15;
	data[4] = LO(center);
	data[5] = HI(center);

	db = (1000 * db) >> 16;
	data[6] = LO(db);
	data[7] = HI(db);

	data[8] = (100 * rsat) >> 16;
	data[9] = (100 * lsat) >> 16;

	iforce_send_packet(iforce, FF_CMD_CONDITION, data);
	iforce_dump_packet("condition", FF_CMD_CONDITION, data);

	return 0;
}