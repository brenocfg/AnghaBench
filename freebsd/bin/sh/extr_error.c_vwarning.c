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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 scalar_t__ arg0 ; 
 scalar_t__ commandname ; 
 int /*<<< orphan*/  doformat (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out2 ; 
 int /*<<< orphan*/  out2fmt_flush (char*) ; 
 int /*<<< orphan*/  outfmt (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
vwarning(const char *msg, va_list ap)
{
	if (commandname)
		outfmt(out2, "%s: ", commandname);
	else if (arg0)
		outfmt(out2, "%s: ", arg0);
	doformat(out2, msg, ap);
	out2fmt_flush("\n");
}