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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct map {int /*<<< orphan*/  (* map_ip ) (struct map*,int /*<<< orphan*/ ) ;} ;
struct machine {int dummy; } ;
struct dso {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dso__data_read_offset (struct dso*,struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct map*,int /*<<< orphan*/ ) ; 

ssize_t dso__data_read_addr(struct dso *dso, struct map *map,
			    struct machine *machine, u64 addr,
			    u8 *data, ssize_t size)
{
	u64 offset = map->map_ip(map, addr);
	return dso__data_read_offset(dso, machine, offset, data, size);
}