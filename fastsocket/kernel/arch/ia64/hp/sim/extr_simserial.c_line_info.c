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
struct serial_state {size_t type; int /*<<< orphan*/  irq; int /*<<< orphan*/  port; int /*<<< orphan*/  line; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* uart_config ; 

__attribute__((used)) static inline void line_info(struct seq_file *m, struct serial_state *state)
{
	seq_printf(m, "%d: uart:%s port:%lX irq:%d\n",
		       state->line, uart_config[state->type].name,
		       state->port, state->irq);
}