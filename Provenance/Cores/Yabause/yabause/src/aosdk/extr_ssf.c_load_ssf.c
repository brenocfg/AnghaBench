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
struct TYPE_3__ {int /*<<< orphan*/ * info; int /*<<< orphan*/ * title; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AO_SUCCESS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (unsigned char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (long) ; 
 int /*<<< orphan*/  ssf_fill_info (TYPE_1__*) ; 
 TYPE_1__ ssf_info ; 
 int ssf_start (unsigned char*,long,int,int) ; 
 int /*<<< orphan*/  upper_case (int /*<<< orphan*/ ) ; 

int load_ssf(char *filename, int m68k_core, int sndcore)
{
	long size;
	FILE *fp = fopen(filename, "rb");
	unsigned char *buffer;
	int ret;
   int i;
   size_t fread_val = 0;

	if (!fp)
		return 0;//false

	// Get file size
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = (unsigned char *)malloc(size);

	if (buffer == NULL)
	{
		fclose(fp);
		return 0;//false
	}

   fread_val = fread(buffer, 1, size, fp);
	fclose(fp);

	// Read ID
	if (buffer[0] != 0x50 || buffer[1] != 0x53 ||
		buffer[2] != 0x46 || buffer[3] != 0x11)
	{
		// Can't identify file
		return 0;//false
	}

	if ((ret = ssf_start(buffer, size, m68k_core, sndcore)) != AO_SUCCESS)
	{
		free(buffer);
		return ret;
	}

   ssf_fill_info(&ssf_info);

   for (i = 0; i < 9; i++)
   {
      upper_case(ssf_info.title[i]);
      upper_case(ssf_info.info[i]);
   }

	return 1;//true
}