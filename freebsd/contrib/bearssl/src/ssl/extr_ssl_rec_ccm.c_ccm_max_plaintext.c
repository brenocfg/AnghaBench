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
struct TYPE_3__ {size_t tag_len; } ;
typedef  TYPE_1__ br_sslrec_ccm_context ;

/* Variables and functions */

__attribute__((used)) static void
ccm_max_plaintext(const br_sslrec_ccm_context *cc,
	size_t *start, size_t *end)
{
	size_t len;

	*start += 8;
	len = *end - *start - cc->tag_len;
	if (len > 16384) {
		len = 16384;
	}
	*end = *start + len;
}