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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct readelf {int /*<<< orphan*/  elf; } ;

/* Variables and functions */
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/  elf_errno () ; 
 char* elf_strptr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
dyn_str(struct readelf *re, uint32_t stab, uint64_t d_val)
{
	const char *name;

	if (stab == SHN_UNDEF)
		name = "ERROR";
	else if ((name = elf_strptr(re->elf, stab, d_val)) == NULL) {
		(void) elf_errno(); /* clear error */
		name = "ERROR";
	}

	return (name);
}