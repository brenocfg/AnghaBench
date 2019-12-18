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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 double I_FloatTime () ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  WriteMapFileSafe (int /*<<< orphan*/ *) ; 
 double c_writtenbrushes ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 

void WriteMapFile(char *filename)
{
	FILE *fp;
	double start_time;

	c_writtenbrushes = 0;
	//the time started
	start_time = I_FloatTime();
	//
	Log_Print("writing %s\n", filename);
	fp = fopen(filename, "wb");
	if (!fp)
	{
		Log_Print("can't open %s\n", filename);
		return;
	} //end if
	if (!WriteMapFileSafe(fp))
	{
		fclose(fp);
		Log_Print("error writing map file %s\n", filename);
		return;
	} //end if
	fclose(fp);
	//display creation time
	Log_Print("written %d brushes\n", c_writtenbrushes);
	Log_Print("map file written in %5.0f seconds\n", I_FloatTime() - start_time);
}