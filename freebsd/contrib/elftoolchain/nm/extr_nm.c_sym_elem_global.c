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
typedef  char GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SYM_TYPE (unsigned char) ; 
 int /*<<< orphan*/  UNUSED (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ isupper (unsigned char) ; 

__attribute__((used)) static int
sym_elem_global(char type, const GElf_Sym *sym, const char *name)
{

	assert(IS_SYM_TYPE((unsigned char) type));

	UNUSED(sym);
	UNUSED(name);

	/* weak symbols resemble global. */
	return (isupper((unsigned char) type) || type == 'w');
}