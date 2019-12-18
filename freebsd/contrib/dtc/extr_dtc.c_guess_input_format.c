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
typedef  scalar_t__ uint32_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ FDT_MAGIC ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fdt32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 char const* guess_type_by_name (char const*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static const char *guess_input_format(const char *fname, const char *fallback)
{
	struct stat statbuf;
	uint32_t magic;
	FILE *f;

	if (stat(fname, &statbuf) != 0)
		return fallback;

	if (S_ISDIR(statbuf.st_mode))
		return "fs";

	if (!S_ISREG(statbuf.st_mode))
		return fallback;

	f = fopen(fname, "r");
	if (f == NULL)
		return fallback;
	if (fread(&magic, 4, 1, f) != 1) {
		fclose(f);
		return fallback;
	}
	fclose(f);

	magic = fdt32_to_cpu(magic);
	if (magic == FDT_MAGIC)
		return "dtb";

	return guess_type_by_name(fname, fallback);
}