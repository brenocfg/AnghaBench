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
typedef  int /*<<< orphan*/  unwind_entry_cb_t ;
typedef  int /*<<< orphan*/  unw_word_t ;
typedef  int /*<<< orphan*/  unw_cursor_t ;
typedef  int /*<<< orphan*/  unw_addr_space_t ;
struct unwind_info {int /*<<< orphan*/  machine; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  UNW_REG_IP ; 
 int /*<<< orphan*/  accessors ; 
 int /*<<< orphan*/  display_error (int) ; 
 int entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  unw_create_addr_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unw_destroy_addr_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unw_get_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int unw_init_remote (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unwind_info*) ; 
 scalar_t__ unw_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_entries(struct unwind_info *ui, unwind_entry_cb_t cb,
		       void *arg)
{
	unw_addr_space_t addr_space;
	unw_cursor_t c;
	int ret;

	addr_space = unw_create_addr_space(&accessors, 0);
	if (!addr_space) {
		pr_err("unwind: Can't create unwind address space.\n");
		return -ENOMEM;
	}

	ret = unw_init_remote(&c, addr_space, ui);
	if (ret)
		display_error(ret);

	while (!ret && (unw_step(&c) > 0)) {
		unw_word_t ip;

		unw_get_reg(&c, UNW_REG_IP, &ip);
		ret = entry(ip, ui->thread, ui->machine, cb, arg);
	}

	unw_destroy_addr_space(addr_space);
	return ret;
}