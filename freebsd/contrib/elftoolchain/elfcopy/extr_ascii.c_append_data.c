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
typedef  int /*<<< orphan*/  uint8_t ;
struct section {size_t sz; size_t cap; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 size_t _SEC_INIT_CAP ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
append_data(struct section *s, const void *buf, size_t sz)
{
	uint8_t *p;

	if (s->buf == NULL) {
		s->sz = 0;
		s->cap = _SEC_INIT_CAP;
		if ((s->buf = malloc(s->cap)) == NULL)
			err(EXIT_FAILURE, "malloc failed");
	}

	while (sz + s->sz > s->cap) {
		s->cap *= 2;
		if ((s->buf = realloc(s->buf, s->cap)) == NULL)
			err(EXIT_FAILURE, "realloc failed");
	}

	p = s->buf;
	memcpy(&p[s->sz], buf, sz);
	s->sz += sz;
}