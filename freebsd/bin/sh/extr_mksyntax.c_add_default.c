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
 int /*<<< orphan*/  add_one (char*,char*) ; 

__attribute__((used)) static void
add_default(void)
{
	add_one("PEOF",                "CEOF");
	add_one("CTLESC",              "CCTL");
	add_one("CTLVAR",              "CCTL");
	add_one("CTLENDVAR",           "CCTL");
	add_one("CTLBACKQ",            "CCTL");
	add_one("CTLBACKQ + CTLQUOTE", "CCTL");
	add_one("CTLARI",              "CCTL");
	add_one("CTLENDARI",           "CCTL");
	add_one("CTLQUOTEMARK",        "CCTL");
	add_one("CTLQUOTEEND",         "CCTL");
}