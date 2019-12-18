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
typedef  scalar_t__ unw_word_t ;
typedef  int /*<<< orphan*/  u8 ;
struct unwind_info {int /*<<< orphan*/  machine; int /*<<< orphan*/  thread; } ;
struct addr_location {TYPE_1__* map; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP__FUNCTION ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 int dso__data_read_addr (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  thread__find_addr_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct addr_location*) ; 

__attribute__((used)) static int access_dso_mem(struct unwind_info *ui, unw_word_t addr,
			  unw_word_t *data)
{
	struct addr_location al;
	ssize_t size;

	thread__find_addr_map(ui->thread, ui->machine, PERF_RECORD_MISC_USER,
			      MAP__FUNCTION, addr, &al);
	if (!al.map) {
		pr_debug("unwind: no map for %lx\n", (unsigned long)addr);
		return -1;
	}

	if (!al.map->dso)
		return -1;

	size = dso__data_read_addr(al.map->dso, al.map, ui->machine,
				   addr, (u8 *) data, sizeof(*data));

	return !(size == sizeof(*data));
}