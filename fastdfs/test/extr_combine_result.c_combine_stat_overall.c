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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 char* STAT_FILENAME_BY_OVERALL ; 
 char* STRERROR (int) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 int proccess_count ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 

__attribute__((used)) static int combine_stat_overall(int *ptotal_count, int *psuccess_count, int *ptime_used)
{
	char filename[64];
	FILE *fp;
	int proccess_index;
	char buff[256];
	int time_used;
	int total_count;
	int success_count;

	*ptotal_count = 0;
	*psuccess_count = 0; 
	*ptime_used = 0;

	for (proccess_index=0; proccess_index<proccess_count; proccess_index++)
	{
		sprintf(filename, "%s.%d", STAT_FILENAME_BY_OVERALL, proccess_index);
		if ((fp=fopen(filename, "r")) == NULL)
		{
			printf("open file %s fail, errno: %d, error info: %s\n", 
				filename, errno, STRERROR(errno));
			return errno != 0 ? errno : EPERM;
		}

		while (fgets(buff, sizeof(buff), fp) != NULL)
		{
			if (*buff == '#')
			{
				continue;
			}

			if (sscanf(buff, "%d %d %d", &total_count, &success_count, &time_used) != 3)
			{
				printf("sscanf %s fail, errno: %d, error info: %s\n", 
					filename, errno, STRERROR(errno));
				return errno != 0 ? errno : EINVAL;
			}

			break;
		}

		*ptotal_count += total_count;
		*psuccess_count += success_count; 
		*ptime_used += time_used;
		fclose(fp);
	}

	*ptime_used /= proccess_count;

	return 0;
}