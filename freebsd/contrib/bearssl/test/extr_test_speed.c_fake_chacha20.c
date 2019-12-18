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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
fake_chacha20(const void *key, const void *iv,
	uint32_t cc, void *data, size_t len)
{
	(void)key;
	(void)iv;
	(void)data;
	(void)len;
	return cc + (uint32_t)((len + 63) >> 6);
}