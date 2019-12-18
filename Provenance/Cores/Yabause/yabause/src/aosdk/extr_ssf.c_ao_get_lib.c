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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AO_FAIL ; 
 int AO_SUCCESS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int ao_get_lib(char *filename, u8 **buffer, u64 *length)
{
	u8 *filebuf;
	u32 size;
	FILE *auxfile;
   size_t fread_val = 0;

	auxfile = fopen(filename, "rb");
	if (!auxfile)
	{
		printf("Unable to find auxiliary file %s\n", filename);
		return AO_FAIL;
	}

	fseek(auxfile, 0, SEEK_END);
	size = ftell(auxfile);
	fseek(auxfile, 0, SEEK_SET);

	filebuf = malloc(size);

	if (!filebuf)
	{
		fclose(auxfile);
		printf("ERROR: could not allocate %d bytes of memory\n", size);
		return AO_FAIL;
	}

   fread_val = fread(filebuf, size, 1, auxfile);
	fclose(auxfile);

	*buffer = filebuf;
	*length = (u64)size;

	return AO_SUCCESS;
}