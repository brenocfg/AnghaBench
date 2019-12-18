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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  MCS_TAG_DOMAIN_PARAMS ; 
 int /*<<< orphan*/  ber_out_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ber_out_integer (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mcs_out_domain_params(STREAM s, int max_channels, int max_users, int max_tokens, int max_pdusize)
{
	ber_out_header(s, MCS_TAG_DOMAIN_PARAMS, 32);
	ber_out_integer(s, max_channels);
	ber_out_integer(s, max_users);
	ber_out_integer(s, max_tokens);
	ber_out_integer(s, 1);	/* num_priorities */
	ber_out_integer(s, 0);	/* min_throughput */
	ber_out_integer(s, 1);	/* max_height */
	ber_out_integer(s, max_pdusize);
	ber_out_integer(s, 2);	/* ver_protocol */
}