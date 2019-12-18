#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct TYPE_3__ {int d86_len; int d86_error; int (* d86_get_byte ) (int /*<<< orphan*/ ) ;int* d86_bytes; int /*<<< orphan*/  d86_data; } ;
typedef  TYPE_1__ dis86_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_get_opcode(dis86_t *x, uint_t *high, uint_t *low)
{
	int byte;

	/*
	 * x86 instructions have a maximum length of 15 bytes.  Bail out if
	 * we try to read more.
	 */
	if (x->d86_len >= 15)
		return (x->d86_error = 1);

	if (x->d86_error)
		return (1);
	byte = x->d86_get_byte(x->d86_data);
	if (byte < 0)
		return (x->d86_error = 1);
	x->d86_bytes[x->d86_len++] = byte;
	*low = byte & 0xf;		/* ----xxxx low 4 bits */
	*high = byte >> 4 & 0xf;	/* xxxx---- bits 7 to 4 */
	return (0);
}