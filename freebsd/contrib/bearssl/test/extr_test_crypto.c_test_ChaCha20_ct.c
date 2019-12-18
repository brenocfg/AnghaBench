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

/* Variables and functions */
 int /*<<< orphan*/  br_chacha20_ct_run ; 
 int /*<<< orphan*/  test_ChaCha20_generic (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_ChaCha20_ct(void)
{
	test_ChaCha20_generic("ChaCha20_ct", &br_chacha20_ct_run);
}