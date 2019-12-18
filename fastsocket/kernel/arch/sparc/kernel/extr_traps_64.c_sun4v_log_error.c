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
struct sun4v_error_entry {int err_attrs; int /*<<< orphan*/  err_cpu; int /*<<< orphan*/  err_size; int /*<<< orphan*/  err_raddr; int /*<<< orphan*/  err_type; int /*<<< orphan*/  err_stick; int /*<<< orphan*/  err_handle; } ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int SUN4V_ERR_ATTRS_FPU_REGISTERS ; 
 int SUN4V_ERR_ATTRS_INT_REGISTERS ; 
 int SUN4V_ERR_ATTRS_MEMORY ; 
 int SUN4V_ERR_ATTRS_PIO ; 
 int SUN4V_ERR_ATTRS_PRIV_MODE ; 
 int SUN4V_ERR_ATTRS_PROCESSOR ; 
 int SUN4V_ERR_ATTRS_RES_QUEUE_FULL ; 
 int SUN4V_ERR_ATTRS_USER_MODE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,char const*,int,...) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  sun4v_err_type_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sun4v_log_error(struct pt_regs *regs, struct sun4v_error_entry *ent, int cpu, const char *pfx, atomic_t *ocnt)
{
	int cnt;

	printk("%s: Reporting on cpu %d\n", pfx, cpu);
	printk("%s: err_handle[%llx] err_stick[%llx] err_type[%08x:%s]\n",
	       pfx,
	       ent->err_handle, ent->err_stick,
	       ent->err_type,
	       sun4v_err_type_to_str(ent->err_type));
	printk("%s: err_attrs[%08x:%s %s %s %s %s %s %s %s]\n",
	       pfx,
	       ent->err_attrs,
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_PROCESSOR) ?
		"processor" : ""),
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_MEMORY) ?
		"memory" : ""),
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_PIO) ?
		"pio" : ""),
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_INT_REGISTERS) ?
		"integer-regs" : ""),
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_FPU_REGISTERS) ?
		"fpu-regs" : ""),
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_USER_MODE) ?
		"user" : ""),
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_PRIV_MODE) ?
		"privileged" : ""),
	       ((ent->err_attrs & SUN4V_ERR_ATTRS_RES_QUEUE_FULL) ?
		"queue-full" : ""));
	printk("%s: err_raddr[%016llx] err_size[%u] err_cpu[%u]\n",
	       pfx,
	       ent->err_raddr, ent->err_size, ent->err_cpu);

	show_regs(regs);

	if ((cnt = atomic_read(ocnt)) != 0) {
		atomic_set(ocnt, 0);
		wmb();
		printk("%s: Queue overflowed %d times.\n",
		       pfx, cnt);
	}
}