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
struct elfcopy {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_append_section (struct elfcopy*,char const*) ; 
 scalar_t__ is_compress_section (struct elfcopy*,char const*) ; 

__attribute__((used)) static int
is_modify_section(struct elfcopy *ecp, const char *name)
{

	if (is_append_section(ecp, name) ||
	    is_compress_section(ecp, name))
		return (1);

	return (0);
}