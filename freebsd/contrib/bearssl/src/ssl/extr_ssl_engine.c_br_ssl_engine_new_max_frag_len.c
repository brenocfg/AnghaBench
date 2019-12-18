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
struct TYPE_3__ {unsigned int max_frag_len; unsigned int oxc; size_t oxa; size_t oxb; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */

void
br_ssl_engine_new_max_frag_len(br_ssl_engine_context *rc, unsigned max_frag_len)
{
	size_t nxb;

	rc->max_frag_len = max_frag_len;
	nxb = rc->oxc + max_frag_len;
	if (rc->oxa < rc->oxb && rc->oxb > nxb && rc->oxa < nxb) {
		rc->oxb = nxb;
	}
}