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
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 int EI_NIDENT ; 
#define  ELFCLASS32 131 
#define  ELFCLASS64 130 
#define  ELFDATA2LSB 129 
#define  ELFDATA2MSB 128 
 char* ELFMAG ; 
 int SELFMAG ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(int argc, char **argv)
{
	unsigned char ei[EI_NIDENT];
	union { short s; char c[2]; } endian_test;

	if (argc != 2) {
		fprintf(stderr, "Error: no arch\n");
	}
	if (fread(ei, 1, EI_NIDENT, stdin) != EI_NIDENT) {
		fprintf(stderr, "Error: input truncated\n");
		return 1;
	}
	if (memcmp(ei, ELFMAG, SELFMAG) != 0) {
		fprintf(stderr, "Error: not ELF\n");
		return 1;
	}
	switch (ei[EI_CLASS]) {
	case ELFCLASS32:
		printf("#define KERNEL_ELFCLASS ELFCLASS32\n");
		break;
	case ELFCLASS64:
		printf("#define KERNEL_ELFCLASS ELFCLASS64\n");
		break;
	default:
		exit(1);
	}
	switch (ei[EI_DATA]) {
	case ELFDATA2LSB:
		printf("#define KERNEL_ELFDATA ELFDATA2LSB\n");
		break;
	case ELFDATA2MSB:
		printf("#define KERNEL_ELFDATA ELFDATA2MSB\n");
		break;
	default:
		exit(1);
	}

	if (sizeof(unsigned long) == 4) {
		printf("#define HOST_ELFCLASS ELFCLASS32\n");
	} else if (sizeof(unsigned long) == 8) {
		printf("#define HOST_ELFCLASS ELFCLASS64\n");
	}

	endian_test.s = 0x0102;
	if (memcmp(endian_test.c, "\x01\x02", 2) == 0)
		printf("#define HOST_ELFDATA ELFDATA2MSB\n");
	else if (memcmp(endian_test.c, "\x02\x01", 2) == 0)
		printf("#define HOST_ELFDATA ELFDATA2LSB\n");
	else
		exit(1);

	if ((strcmp(argv[1], "h8300") == 0)
	    || (strcmp(argv[1], "blackfin") == 0))
		printf("#define MODULE_SYMBOL_PREFIX \"_\"\n");
	else
		printf("#define MODULE_SYMBOL_PREFIX \"\"\n");

	return 0;
}