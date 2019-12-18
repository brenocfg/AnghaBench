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
typedef  int /*<<< orphan*/  br_sslrec_chapol_context ;

/* Variables and functions */

__attribute__((used)) static int
chapol_check_length(const br_sslrec_chapol_context *cc, size_t rlen)
{
	/*
	 * Overhead is just the authentication tag (16 bytes).
	 */
	(void)cc;
	return rlen >= 16 && rlen <= (16384 + 16);
}