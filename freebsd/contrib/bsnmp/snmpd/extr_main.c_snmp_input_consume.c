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
struct port_input {scalar_t__ length; scalar_t__ consumed; scalar_t__ buf; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
snmp_input_consume(struct port_input *pi)
{
	if (!pi->stream) {
		/* always consume everything */
		pi->length = 0;
		return;
	}
	if (pi->consumed >= pi->length) {
		/* all bytes consumed */
		pi->length = 0;
		return;
	}
	memmove(pi->buf, pi->buf + pi->consumed, pi->length - pi->consumed);
	pi->length -= pi->consumed;
}