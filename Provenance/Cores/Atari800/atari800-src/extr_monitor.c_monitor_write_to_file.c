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
typedef  int UWORD ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * MEMORY_mem ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ get_hex2 (int*,int*) ; 
 char* get_token () ; 
 int /*<<< orphan*/  perror (char const*) ; 

__attribute__((used)) static void monitor_write_to_file(void)
{
	UWORD addr1;
	UWORD addr2;
	if (get_hex2(&addr1, &addr2) && addr1 <= addr2) {
		const char *filename;
		FILE *f;
		filename = get_token();
		if (filename == NULL)
			filename = "memdump.dat";
		f = fopen(filename, "wb");
		if (f == NULL)
			perror(filename);
		else {
			size_t nbytes = addr2 - addr1 + 1;
			if (fwrite(&MEMORY_mem[addr1], 1, addr2 - addr1 + 1, f) < nbytes)
				perror(filename);
			fclose(f);
		}
	}
}