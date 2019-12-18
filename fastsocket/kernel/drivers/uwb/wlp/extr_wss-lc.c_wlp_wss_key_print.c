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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t wlp_wss_key_print(char *buf, size_t bufsize, u8 *key)
{
	size_t result;

	result = scnprintf(buf, bufsize,
			  "%02x %02x %02x %02x %02x %02x "
			  "%02x %02x %02x %02x %02x %02x "
			  "%02x %02x %02x %02x",
			  key[0], key[1], key[2], key[3],
			  key[4], key[5], key[6], key[7],
			  key[8], key[9], key[10], key[11],
			  key[12], key[13], key[14], key[15]);
	return result;
}