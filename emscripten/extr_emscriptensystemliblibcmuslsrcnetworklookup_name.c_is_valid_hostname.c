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
 scalar_t__ isalnum (unsigned char const) ; 
 int mbstowcs (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int strnlen (char const*,int) ; 

__attribute__((used)) static int is_valid_hostname(const char *host)
{
	const unsigned char *s;
	if (strnlen(host, 255)-1 >= 254 || mbstowcs(0, host, 0) == -1) return 0;
	for (s=(void *)host; *s>=0x80 || *s=='.' || *s=='-' || isalnum(*s); s++);
	return !*s;
}