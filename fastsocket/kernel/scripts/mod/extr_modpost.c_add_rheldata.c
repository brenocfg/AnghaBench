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
struct module {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RHEL_MAJOR ; 
 int /*<<< orphan*/  RHEL_MINOR ; 
 int /*<<< orphan*/  buf_printf (struct buffer*,char*,...) ; 

__attribute__((used)) static void add_rheldata(struct buffer *b, struct module *mod)
{
	buf_printf(b, "\n");
	buf_printf(b, "static const struct rheldata _rheldata __used\n");
	buf_printf(b, "__attribute__((section(\".rheldata\"))) = {\n");
	buf_printf(b, "	.rhel_major = %d,\n", RHEL_MAJOR);
	buf_printf(b, "	.rhel_minor = %d,\n", RHEL_MINOR);
	buf_printf(b, "};\n");
}