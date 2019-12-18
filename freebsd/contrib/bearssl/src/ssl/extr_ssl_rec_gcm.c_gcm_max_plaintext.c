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
typedef  int /*<<< orphan*/  br_sslrec_gcm_context ;

/* Variables and functions */

__attribute__((used)) static void
gcm_max_plaintext(const br_sslrec_gcm_context *cc,
	size_t *start, size_t *end)
{
	size_t len;

	(void)cc;
	*start += 8;
	len = *end - *start - 16;
	if (len > 16384) {
		len = 16384;
	}
	*end = *start + len;
}