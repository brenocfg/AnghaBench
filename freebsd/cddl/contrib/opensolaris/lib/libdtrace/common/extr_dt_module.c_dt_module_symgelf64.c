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
typedef  int /*<<< orphan*/  GElf_Sym ;
typedef  int /*<<< orphan*/  Elf64_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static GElf_Sym *
dt_module_symgelf64(const Elf64_Sym *src, GElf_Sym *dst)
{
	if (dst != NULL)
		bcopy(src, dst, sizeof (GElf_Sym));

	return (dst);
}