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
typedef  int /*<<< orphan*/  br_ssl_server_context ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
br_ssl_server_zero(br_ssl_server_context *cc)
{
	/*
	 * For really standard C, we should explicitly set to NULL all
	 * pointers, and 0 all other fields. However, on all our target
	 * architectures, a direct memset() will work, be faster, and
	 * use a lot less code.
	 */
	memset(cc, 0, sizeof *cc);
}