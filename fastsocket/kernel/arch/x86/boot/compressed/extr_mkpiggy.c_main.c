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
typedef  long uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fread (long*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 long getle32 (long*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
	uint32_t olen;
	long ilen;
	unsigned long offs;
	FILE *f;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s compressed_file\n", argv[0]);
		return 1;
	}

	/* Get the information for the compressed kernel image first */

	f = fopen(argv[1], "r");
	if (!f) {
		perror(argv[1]);
		return 1;
	}


	if (fseek(f, -4L, SEEK_END)) {
		perror(argv[1]);
	}
	fread(&olen, sizeof olen, 1, f);
	ilen = ftell(f);
	olen = getle32(&olen);
	fclose(f);

	/*
	 * Now we have the input (compressed) and output (uncompressed)
	 * sizes, compute the necessary decompression offset...
	 */

	offs = (olen > ilen) ? olen - ilen : 0;
	offs += olen >> 12;	/* Add 8 bytes for each 32K block */
	offs += 32*1024 + 18;	/* Add 32K + 18 bytes slack */
	offs = (offs+4095) & ~4095; /* Round to a 4K boundary */

	printf(".section \".rodata.compressed\",\"a\",@progbits\n");
	printf(".globl z_input_len\n");
	printf("z_input_len = %lu\n", ilen);
	printf(".globl z_output_len\n");
	printf("z_output_len = %lu\n", (unsigned long)olen);
	printf(".globl z_extract_offset\n");
	printf("z_extract_offset = 0x%lx\n", offs);
	/* z_extract_offset_negative allows simplification of head_32.S */
	printf(".globl z_extract_offset_negative\n");
	printf("z_extract_offset_negative = -0x%lx\n", offs);

	printf(".globl input_data, input_data_end\n");
	printf("input_data:\n");
	printf(".incbin \"%s\"\n", argv[1]);
	printf("input_data_end:\n");

	return 0;
}