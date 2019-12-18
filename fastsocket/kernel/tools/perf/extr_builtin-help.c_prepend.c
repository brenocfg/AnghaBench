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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const char *prepend(const char *prefix, const char *cmd)
{
	size_t pre_len = strlen(prefix);
	size_t cmd_len = strlen(cmd);
	char *p = malloc(pre_len + cmd_len + 1);
	memcpy(p, prefix, pre_len);
	strcpy(p + pre_len, cmd);
	return p;
}