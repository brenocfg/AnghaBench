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
struct sbuf {scalar_t__ s_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_CLEARFLAG (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBUF_FINISHED ; 
 int /*<<< orphan*/  SBUF_OVERFLOWED ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 

void
sbuf_clear(struct sbuf *s)
{
	assert_sbuf_integrity(s);
	/* don't care if it's finished or not */

	SBUF_CLEARFLAG(s, SBUF_FINISHED);
	SBUF_CLEARFLAG(s, SBUF_OVERFLOWED);
	s->s_len = 0;
}