#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ err; unsigned char const* hbuf; size_t hlen; int /*<<< orphan*/  cpu; } ;
typedef  TYPE_1__ br_x509_minimal_context ;
typedef  int /*<<< orphan*/  br_x509_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_x509_minimal_run (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xm_append(const br_x509_class **ctx, const unsigned char *buf, size_t len)
{
	br_x509_minimal_context *cc;

	cc = (br_x509_minimal_context *)(void *)ctx;
	if (cc->err != 0) {
		return;
	}
	cc->hbuf = buf;
	cc->hlen = len;
	br_x509_minimal_run(&cc->cpu);
}