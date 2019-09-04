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
struct sbuf {int s_size; int s_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 

int
sbuf_setpos(struct sbuf *s, int pos)
{
	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);

	KASSERT(pos >= 0,
	    ("attempt to seek to a negative position (%d)", pos));
	KASSERT(pos < s->s_size,
	    ("attempt to seek past end of sbuf (%d >= %d)", pos, s->s_size));

	if (pos < 0 || pos > s->s_len)
		return (-1);
	s->s_len = pos;
	return (0);
}