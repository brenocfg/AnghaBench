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
typedef  int /*<<< orphan*/  UWORD ;

/* Variables and functions */
 int FALSE ; 
 char* get_token () ; 
 int parse_hex (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_hex(UWORD *hexval)
{
	const char *t;
	t = get_token();
	if (t != NULL)
		return parse_hex(t, hexval);
	return FALSE;
}