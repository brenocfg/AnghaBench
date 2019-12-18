#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* vtable; } ;
struct TYPE_7__ {size_t mac_len; scalar_t__ explicit_IV; TYPE_2__ bc; } ;
typedef  TYPE_3__ br_sslrec_out_cbc_context ;
struct TYPE_5__ {size_t block_size; } ;

/* Variables and functions */

__attribute__((used)) static void
cbc_max_plaintext(const br_sslrec_out_cbc_context *cc,
	size_t *start, size_t *end)
{
	size_t blen, len;

	blen = cc->bc.vtable->block_size;
	if (cc->explicit_IV) {
		*start += blen;
	} else {
		*start += 4 + ((cc->mac_len + blen + 1) & ~(blen - 1));
	}
	len = (*end - *start) & ~(blen - 1);
	len -= 1 + cc->mac_len;
	if (len > 16384) {
		len = 16384;
	}
	*end = *start + len;
}