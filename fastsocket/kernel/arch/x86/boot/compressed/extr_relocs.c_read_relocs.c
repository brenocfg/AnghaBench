#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sh_type; int sh_size; int /*<<< orphan*/  sh_offset; } ;
struct section {TYPE_2__* reltab; TYPE_1__ shdr; } ;
struct TYPE_8__ {int e_shnum; } ;
struct TYPE_7__ {void* r_info; void* r_offset; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ Elf32_Rel ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SHT_REL ; 
 int /*<<< orphan*/  die (char*,int,...) ; 
 TYPE_5__ ehdr ; 
 void* elf32_to_cpu (void*) ; 
 int /*<<< orphan*/  errno ; 
 int fread (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 struct section* secs ; 
 int strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_relocs(FILE *fp)
{
	int i,j;
	for (i = 0; i < ehdr.e_shnum; i++) {
		struct section *sec = &secs[i];
		if (sec->shdr.sh_type != SHT_REL) {
			continue;
		}
		sec->reltab = malloc(sec->shdr.sh_size);
		if (!sec->reltab) {
			die("malloc of %d bytes for relocs failed\n",
				sec->shdr.sh_size);
		}
		if (fseek(fp, sec->shdr.sh_offset, SEEK_SET) < 0) {
			die("Seek to %d failed: %s\n",
				sec->shdr.sh_offset, strerror(errno));
		}
		if (fread(sec->reltab, 1, sec->shdr.sh_size, fp)
		    != sec->shdr.sh_size) {
			die("Cannot read symbol table: %s\n",
				strerror(errno));
		}
		for (j = 0; j < sec->shdr.sh_size/sizeof(Elf32_Rel); j++) {
			Elf32_Rel *rel = &sec->reltab[j];
			rel->r_offset = elf32_to_cpu(rel->r_offset);
			rel->r_info   = elf32_to_cpu(rel->r_info);
		}
	}
}