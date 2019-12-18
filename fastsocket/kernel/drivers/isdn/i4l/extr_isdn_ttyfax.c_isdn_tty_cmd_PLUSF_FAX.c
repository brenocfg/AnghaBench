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
typedef  int /*<<< orphan*/  modem_info ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_ERROR1 ; 
 scalar_t__ TTY_IS_FCLASS1 (int /*<<< orphan*/ *) ; 
 scalar_t__ TTY_IS_FCLASS2 (int /*<<< orphan*/ *) ; 
 int isdn_tty_cmd_FCLASS1 (char**,int /*<<< orphan*/ *) ; 
 int isdn_tty_cmd_FCLASS2 (char**,int /*<<< orphan*/ *) ; 

int
isdn_tty_cmd_PLUSF_FAX(char **p, modem_info * info)
{
	if (TTY_IS_FCLASS2(info))
		return (isdn_tty_cmd_FCLASS2(p, info));
	else if (TTY_IS_FCLASS1(info))
		return (isdn_tty_cmd_FCLASS1(p, info));
	PARSE_ERROR1;
}