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
typedef  int /*<<< orphan*/  const utf32_t ;

/* Variables and functions */
 int /*<<< orphan*/  const EOS ; 
 int /*<<< orphan*/  assert (int) ; 

utf32_t lb_get_next_char_utf32(
		const utf32_t *s,
		size_t len,
		size_t *ip)
{
	assert(*ip <= len);
	if (*ip == len)
		return EOS;
	return s[(*ip)++];
}