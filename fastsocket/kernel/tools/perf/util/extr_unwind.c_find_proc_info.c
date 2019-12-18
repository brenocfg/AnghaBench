#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unw_word_t ;
typedef  int /*<<< orphan*/  unw_proc_info_t ;
struct TYPE_7__ {int segbase; int table_data; int table_len; } ;
struct TYPE_8__ {TYPE_1__ rti; } ;
struct TYPE_9__ {int start_ip; TYPE_2__ u; int /*<<< orphan*/  end_ip; int /*<<< orphan*/  format; } ;
typedef  TYPE_3__ unw_dyn_info_t ;
typedef  int /*<<< orphan*/  unw_addr_space_t ;
typedef  int u64 ;
struct unwind_info {int /*<<< orphan*/  machine; } ;
struct table_entry {int dummy; } ;
struct map {int start; int /*<<< orphan*/  end; TYPE_4__* dso; } ;
typedef  int /*<<< orphan*/  di ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UNW_INFO_FORMAT_REMOTE_TABLE ; 
 int dwarf_search_unwind_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int,void*) ; 
 struct map* find_map (int /*<<< orphan*/ ,struct unwind_info*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_unwind_spec (TYPE_4__*,int /*<<< orphan*/ ,int*,int*,int*) ; 

__attribute__((used)) static int
find_proc_info(unw_addr_space_t as, unw_word_t ip, unw_proc_info_t *pi,
	       int need_unwind_info, void *arg)
{
	struct unwind_info *ui = arg;
	struct map *map;
	unw_dyn_info_t di;
	u64 table_data, segbase, fde_count;

	map = find_map(ip, ui);
	if (!map || !map->dso)
		return -EINVAL;

	pr_debug("unwind: find_proc_info dso %s\n", map->dso->name);

	if (read_unwind_spec(map->dso, ui->machine,
			     &table_data, &segbase, &fde_count))
		return -EINVAL;

	memset(&di, 0, sizeof(di));
	di.format   = UNW_INFO_FORMAT_REMOTE_TABLE;
	di.start_ip = map->start;
	di.end_ip   = map->end;
	di.u.rti.segbase    = map->start + segbase;
	di.u.rti.table_data = map->start + table_data;
	di.u.rti.table_len  = fde_count * sizeof(struct table_entry)
			      / sizeof(unw_word_t);
	return dwarf_search_unwind_table(as, ip, &di, pi,
					 need_unwind_info, arg);
}