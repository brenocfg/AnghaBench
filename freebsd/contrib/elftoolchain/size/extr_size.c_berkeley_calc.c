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
struct TYPE_3__ {int sh_flags; scalar_t__ sh_type; scalar_t__ sh_size; } ;
typedef  TYPE_1__ GElf_Shdr ;

/* Variables and functions */
 int SHF_ALLOC ; 
 int SHF_EXECINSTR ; 
 int SHF_WRITE ; 
 scalar_t__ SHT_NOBITS ; 
 int /*<<< orphan*/  bss_size ; 
 int /*<<< orphan*/  data_size ; 
 int /*<<< orphan*/  text_size ; 

__attribute__((used)) static void
berkeley_calc(GElf_Shdr *shdr)
{
	if (shdr != NULL) {
		if (!(shdr->sh_flags & SHF_ALLOC))
			return;
		if ((shdr->sh_flags & SHF_ALLOC) &&
		    ((shdr->sh_flags & SHF_EXECINSTR) ||
		    !(shdr->sh_flags & SHF_WRITE)))
			text_size += shdr->sh_size;
		else if ((shdr->sh_flags & SHF_ALLOC) &&
		    (shdr->sh_flags & SHF_WRITE) &&
		    (shdr->sh_type != SHT_NOBITS))
			data_size += shdr->sh_size;
		else
			bss_size += shdr->sh_size;
	}
}