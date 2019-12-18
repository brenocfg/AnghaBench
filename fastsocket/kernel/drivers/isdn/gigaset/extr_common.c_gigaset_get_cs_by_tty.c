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
struct tty_struct {scalar_t__ index; TYPE_1__* driver; } ;
struct cardstate {int dummy; } ;
struct TYPE_2__ {scalar_t__ num; scalar_t__ minor_start; } ;

/* Variables and functions */
 struct cardstate* gigaset_get_cs_by_minor (scalar_t__) ; 

struct cardstate *gigaset_get_cs_by_tty(struct tty_struct *tty)
{
	if (tty->index < 0 || tty->index >= tty->driver->num)
		return NULL;
	return gigaset_get_cs_by_minor(tty->index + tty->driver->minor_start);
}