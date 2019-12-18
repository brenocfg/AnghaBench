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
typedef  int utf32_t ;
typedef  int utf16_t ;

/* Variables and functions */
 int EOS ; 
 int /*<<< orphan*/  assert (int) ; 

utf32_t lb_get_next_char_utf16(
		const utf16_t *s,
		size_t len,
		size_t *ip)
{
	utf16_t ch;

	assert(*ip <= len);
	if (*ip == len)
		return EOS;
	ch = s[(*ip)++];

	if (ch < 0xD800 || ch > 0xDBFF)
	{	/* If the character is not a high surrogate */
		return ch;
	}
	if (*ip == len)
	{	/* If the input ends here (an error) */
		--(*ip);
		return EOS;
	}
	if (s[*ip] < 0xDC00 || s[*ip] > 0xDFFF)
	{	/* If the next character is not the low surrogate (an error) */
		return ch;
	}
	/* Return the constructed character and advance the index again */
	return (((utf32_t)ch & 0x3FF) << 10) + (s[(*ip)++] & 0x3FF) + 0x10000;
}