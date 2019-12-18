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
struct TYPE_3__ {int tag_len; } ;
typedef  TYPE_1__ br_sslrec_ccm_context ;

/* Variables and functions */

__attribute__((used)) static int
ccm_check_length(const br_sslrec_ccm_context *cc, size_t rlen)
{
	/*
	 * CCM overhead is 8 bytes for nonce_explicit, and the tag
	 * (normally 8 or 16 bytes, depending on cipher suite).
	 */
	size_t over;

	over = 8 + cc->tag_len;
	return rlen >= over && rlen <= (16384 + over);
}