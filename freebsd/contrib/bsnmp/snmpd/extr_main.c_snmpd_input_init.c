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
struct port_input {int fd; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * id; } ;

/* Variables and functions */

void
snmpd_input_init(struct port_input *pi)
{
	pi->id = NULL;
	pi->fd = -1;
	pi->buf = NULL;
}