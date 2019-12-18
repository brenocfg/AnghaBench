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
struct elfdump {int /*<<< orphan*/  elf; } ;

/* Variables and functions */
 char* elf_strptr (int /*<<< orphan*/ ,int,size_t) ; 

__attribute__((used)) static const char*
get_string(struct elfdump *ed, int strtab, size_t off)
{
	const char *name;

	if ((name = elf_strptr(ed->elf, strtab, off)) == NULL)
		return ("");

	return (name);
}