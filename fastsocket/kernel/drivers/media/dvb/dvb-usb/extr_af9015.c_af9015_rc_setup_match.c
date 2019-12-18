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
struct af9015_rc_setup {char* rc_codes; unsigned int id; } ;

/* Variables and functions */

__attribute__((used)) static char *af9015_rc_setup_match(unsigned int id,
	const struct af9015_rc_setup *table)
{
	for (; table->rc_codes; table++)
		if (table->id == id)
			return table->rc_codes;
	return NULL;
}