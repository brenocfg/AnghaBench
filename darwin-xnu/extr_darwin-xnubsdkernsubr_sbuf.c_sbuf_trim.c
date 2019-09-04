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
struct sbuf {int s_len; int /*<<< orphan*/ * s_buf; } ;

/* Variables and functions */
 scalar_t__ SBUF_HASOVERFLOWED (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 

int
sbuf_trim(struct sbuf *s)
{
	assert_sbuf_integrity(s);
	assert_sbuf_state(s, 0);

	if (SBUF_HASOVERFLOWED(s))
		return (-1);

	while (s->s_len && isspace(s->s_buf[s->s_len-1]))
		--s->s_len;

	return (0);
}