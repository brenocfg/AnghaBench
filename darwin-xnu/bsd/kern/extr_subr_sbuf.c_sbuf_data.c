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
struct sbuf {char* s_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FINISHED ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_state (struct sbuf*,int /*<<< orphan*/ ) ; 

char *
sbuf_data(struct sbuf *s)
{
	assert_sbuf_integrity(s);
	assert_sbuf_state(s, SBUF_FINISHED);

	return s->s_buf;
}