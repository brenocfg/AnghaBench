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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  STB_GLOBAL ; 
 int /*<<< orphan*/  STB_LOCAL ; 
 int /*<<< orphan*/  STB_WEAK ; 
 scalar_t__ isupper (char) ; 

__attribute__((used)) static u8 kallsyms2elf_type(char type)
{
	if (type == 'W')
		return STB_WEAK;

	return isupper(type) ? STB_GLOBAL : STB_LOCAL;
}