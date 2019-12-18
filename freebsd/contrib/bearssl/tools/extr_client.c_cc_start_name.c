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
struct TYPE_2__ {scalar_t__ verbose; } ;
typedef  TYPE_1__ ccert_context ;
typedef  int /*<<< orphan*/  br_ssl_client_certificate_class ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
cc_start_name(const br_ssl_client_certificate_class **pctx, size_t len)
{
	ccert_context *zc;

	zc = (ccert_context *)pctx;
	if (zc->verbose) {
		fprintf(stderr, "new anchor name, length = %u\n",
			(unsigned)len);
	}
}