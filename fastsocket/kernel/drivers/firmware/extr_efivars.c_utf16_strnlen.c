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
typedef  int /*<<< orphan*/  efi_char16_t ;

/* Variables and functions */

__attribute__((used)) static unsigned long
utf16_strnlen(efi_char16_t *s, size_t maxlength)
{
	unsigned long length = 0;

	while (*s++ != 0 && length < maxlength)
		length++;
	return length;
}