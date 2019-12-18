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
 int EPERM ; 
 char* STAT_FILENAME_BY_OVERALL ; 
 char* STRERROR (int) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 int proccess_index ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 scalar_t__ start_time ; 
 int success_count ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int total_count ; 

__attribute__((used)) static int save_stats_by_overall()
{
	char filename[64];
	FILE *fp;

	sprintf(filename, "%s.%d", STAT_FILENAME_BY_OVERALL, proccess_index);
	if ((fp=fopen(filename, "wb")) == NULL)
	{
		printf("open file %s fail, errno: %d, error info: %s\n", 
			filename, errno, STRERROR(errno));
		return errno != 0 ? errno : EPERM;
	}

	fprintf(fp, "#total_count success_count  time_used(s)\n");
	fprintf(fp, "%d %d %d\n", total_count, success_count, (int)(time(NULL) - start_time));

	fclose(fp);
	return 0;
}