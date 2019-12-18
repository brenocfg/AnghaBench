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
struct TYPE_2__ {scalar_t__ expires; } ;
struct snd_uart16550 {int timer_running; TYPE_1__ buffer_timer; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static inline void snd_uart16550_add_timer(struct snd_uart16550 *uart)
{
	if (!uart->timer_running) {
		/* timer 38600bps * 10bit * 16byte */
		uart->buffer_timer.expires = jiffies + (HZ+255)/256;
		uart->timer_running = 1;
		add_timer(&uart->buffer_timer);
	}
}