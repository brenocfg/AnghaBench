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
 int /*<<< orphan*/  isalpha (unsigned char) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
istoken(const char *str, const char *tok, size_t len)
{
	return strncmp(str, tok, len) == 0 && !isalpha((unsigned char)str[len]);
}