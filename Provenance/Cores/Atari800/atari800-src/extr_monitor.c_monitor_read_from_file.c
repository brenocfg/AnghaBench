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
 scalar_t__ fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ get_hex2 (int*,int*) ; 
 char* get_token () ; 
 int /*<<< orphan*/  perror (char const*) ; 

__attribute__((used)) static void monitor_read_from_file(UWORD *addr)
{
	const char *filename;
	filename = get_token();
	if (filename != NULL) {
		UWORD nbytes;
		if (get_hex2(addr, &nbytes) && *addr + nbytes <= 0x10000) {
			FILE *f = fopen(filename, "rb");
			if (f == NULL)
				perror(filename);
			else {
				if (fread(&MEMORY_mem[*addr], 1, nbytes, f) == 0)
					perror(filename);
				fclose(f);
			}
		}
	}
}