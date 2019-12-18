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
struct sbuf {int* s_buf; int /*<<< orphan*/  s_len; } ;

/* Variables and functions */
 scalar_t__ SBUF_HASOVERFLOWED (struct sbuf*) ; 
 int /*<<< orphan*/  SBUF_HASROOM (struct sbuf*) ; 
 int /*<<< orphan*/  SBUF_OVERFLOWED ; 
 int /*<<< orphan*/  SBUF_SETFLAG (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbuf_extend (struct sbuf*,int) ; 

int
sbuf_putc(struct sbuf *s, int c)
{
	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);

	if (SBUF_HASOVERFLOWED(s))
		return (-1);

	if (!SBUF_HASROOM(s) && sbuf_extend(s, 1) < 0) {
		SBUF_SETFLAG(s, SBUF_OVERFLOWED);
		return (-1);
	}
	if (c != '\0')
	    s->s_buf[s->s_len++] = c;
	return (0);
}