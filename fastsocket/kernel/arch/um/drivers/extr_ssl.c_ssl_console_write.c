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
struct line {int /*<<< orphan*/  lock; int /*<<< orphan*/  chan_list; } ;
struct console {size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  console_write_chan (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 struct line* serial_lines ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ssl_console_write(struct console *c, const char *string,
			      unsigned len)
{
	struct line *line = &serial_lines[c->index];
	unsigned long flags;

	spin_lock_irqsave(&line->lock, flags);
	console_write_chan(&line->chan_list, string, len);
	spin_unlock_irqrestore(&line->lock, flags);
}