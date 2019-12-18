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
struct TYPE_3__ {size_t len; size_t ptr; size_t buf; } ;
typedef  TYPE_1__ rng_fake_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
rng_fake_generate(rng_fake_ctx *cc, void *dst, size_t len)
{
	if (len > (cc->len - cc->ptr)) {
		fprintf(stderr, "asking for more data than expected\n");
		exit(EXIT_FAILURE);
	}
	memcpy(dst, cc->buf + cc->ptr, len);
	cc->ptr += len;
}