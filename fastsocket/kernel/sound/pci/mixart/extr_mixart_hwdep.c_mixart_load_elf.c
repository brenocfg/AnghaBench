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
typedef  scalar_t__ u32 ;
struct snd_mixart_elf32_phdr {scalar_t__ p_type; scalar_t__ p_filesz; scalar_t__ p_vaddr; scalar_t__ p_offset; } ;
struct snd_mixart_elf32_ehdr {char* e_ident; scalar_t__ e_phoff; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_phnum; } ;
struct mixart_mgr {int dummy; } ;
struct firmware {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  elf_programheader ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIXART_MEM (struct mixart_mgr*,scalar_t__) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (struct snd_mixart_elf32_phdr*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mixart_load_elf(struct mixart_mgr *mgr, const struct firmware *dsp )
{
	char                    elf32_magic_number[4] = {0x7f,'E','L','F'};
	struct snd_mixart_elf32_ehdr *elf_header;
	int                     i;

	elf_header = (struct snd_mixart_elf32_ehdr *)dsp->data;
	for( i=0; i<4; i++ )
		if ( elf32_magic_number[i] != elf_header->e_ident[i] )
			return -EINVAL;

	if( elf_header->e_phoff != 0 ) {
		struct snd_mixart_elf32_phdr     elf_programheader;

		for( i=0; i < be16_to_cpu(elf_header->e_phnum); i++ ) {
			u32 pos = be32_to_cpu(elf_header->e_phoff) + (u32)(i * be16_to_cpu(elf_header->e_phentsize));

			memcpy( &elf_programheader, dsp->data + pos, sizeof(elf_programheader) );

			if(elf_programheader.p_type != 0) {
				if( elf_programheader.p_filesz != 0 ) {
					memcpy_toio( MIXART_MEM( mgr, be32_to_cpu(elf_programheader.p_vaddr)),
						     dsp->data + be32_to_cpu( elf_programheader.p_offset ),
						     be32_to_cpu( elf_programheader.p_filesz ));
				}
			}
		}
	}
	return 0;
}