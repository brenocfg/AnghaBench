#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* sh_entsize; void* sh_addralign; void* sh_info; void* sh_link; void* sh_size; void* sh_offset; void* sh_addr; void* sh_flags; void* sh_type; void* sh_name; } ;
typedef  TYPE_1__ Elf32_Shdr ;

/* Variables and functions */
 void* swab32 (void*) ; 

__attribute__((used)) static void convert_elf_shdrs(Elf32_Shdr * s, int num)
{
	int i;

	for (i = 0; i < num; i++, s++) {
		s->sh_name = swab32(s->sh_name);
		s->sh_type = swab32(s->sh_type);
		s->sh_flags = swab32(s->sh_flags);
		s->sh_addr = swab32(s->sh_addr);
		s->sh_offset = swab32(s->sh_offset);
		s->sh_size = swab32(s->sh_size);
		s->sh_link = swab32(s->sh_link);
		s->sh_info = swab32(s->sh_info);
		s->sh_addralign = swab32(s->sh_addralign);
		s->sh_entsize = swab32(s->sh_entsize);
	}
}