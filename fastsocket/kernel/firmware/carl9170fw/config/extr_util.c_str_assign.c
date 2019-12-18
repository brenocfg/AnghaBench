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
struct gstr {scalar_t__ max_width; scalar_t__ len; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct gstr str_assign(const char *s)
{
	struct gstr gs;
	gs.s = strdup(s);
	gs.len = strlen(s) + 1;
	gs.max_width = 0;
	return gs;
}