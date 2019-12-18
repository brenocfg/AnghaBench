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
struct rtas_error_log {int dummy; } ;
struct pt_regs {unsigned long* gpr; } ;
struct TYPE_2__ {unsigned long base; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAS_ERROR_LOG_MAX ; 
 unsigned long* __va (unsigned long) ; 
 scalar_t__ mce_data_buf ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__ rtas ; 

__attribute__((used)) static struct rtas_error_log *fwnmi_get_errinfo(struct pt_regs *regs)
{
	unsigned long errdata = regs->gpr[3];
	struct rtas_error_log *errhdr = NULL;
	unsigned long *savep;

	if ((errdata >= 0x7000 && errdata < 0x7fff0) ||
	    (errdata >= rtas.base && errdata < rtas.base + rtas.size - 16)) {
		savep = __va(errdata);
		regs->gpr[3] = savep[0];	/* restore original r3 */
		memset(mce_data_buf, 0, RTAS_ERROR_LOG_MAX);
		memcpy(mce_data_buf, (char *)(savep + 1), RTAS_ERROR_LOG_MAX);
		errhdr = (struct rtas_error_log *)mce_data_buf;
	} else {
		printk("FWNMI: corrupt r3\n");
	}
	return errhdr;
}