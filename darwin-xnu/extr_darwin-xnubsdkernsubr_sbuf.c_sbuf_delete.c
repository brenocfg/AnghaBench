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
struct sbuf {struct sbuf* s_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBFREE (struct sbuf*) ; 
 scalar_t__ SBUF_ISDYNAMIC (struct sbuf*) ; 
 int SBUF_ISDYNSTRUCT (struct sbuf*) ; 
 int /*<<< orphan*/  assert_sbuf_integrity (struct sbuf*) ; 
 int /*<<< orphan*/  bzero (struct sbuf*,int) ; 

void
sbuf_delete(struct sbuf *s)
{
	int isdyn;

	assert_sbuf_integrity(s);
	/* don't care if it's finished or not */

	if (SBUF_ISDYNAMIC(s))
		SBFREE(s->s_buf);
	isdyn = SBUF_ISDYNSTRUCT(s);
	bzero(s, sizeof *s);
	if (isdyn)
		SBFREE(s);
}