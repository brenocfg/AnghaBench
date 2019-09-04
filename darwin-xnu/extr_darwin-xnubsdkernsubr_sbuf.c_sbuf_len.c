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
struct sbuf {int s_len; } ;

/* Variables and functions */
 scalar_t__ SBUF_HASOVERFLOWED (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 

int
sbuf_len(struct sbuf *s)
{
	assert_sbuf_integrity(s);
	/* don't care if it's finished or not */

	if (SBUF_HASOVERFLOWED(s))
		return (-1);
	return s->s_len;
}