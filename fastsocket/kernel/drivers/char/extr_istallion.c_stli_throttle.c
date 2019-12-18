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
struct tty_struct {struct stliport* driver_data; } ;
struct stliport {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_RXSTOP ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stli_throttle(struct tty_struct *tty)
{
	struct stliport	*portp = tty->driver_data;
	if (portp == NULL)
		return;
	set_bit(ST_RXSTOP, &portp->state);
}