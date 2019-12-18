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
 unsigned long atol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  read_obj (char const*) ; 

__attribute__((used)) static unsigned long get_obj(const char *name)
{
	if (!read_obj(name))
		return 0;

	return atol(buffer);
}