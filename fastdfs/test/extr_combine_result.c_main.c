#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_4__ {int success_count; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ EntryStat ;

/* Variables and functions */
 int EINVAL ; 
 int FILE_TYPE_COUNT ; 
 int /*<<< orphan*/  STAT_FILENAME_BY_FILE_TYPE ; 
 int /*<<< orphan*/  STAT_FILENAME_BY_STORAGE_IP ; 
 int atoi (char*) ; 
 scalar_t__ combine_stat_by (int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  combine_stat_overall (int*,int*,int*) ; 
 int /*<<< orphan*/  print_stat_by (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int proccess_count ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int main(int argc, char **argv)
{
	EntryStat stats[FILE_TYPE_COUNT];
	int entry_count;
	int time_used;
	int total_count;
	int success_count;
	int i;
	int bytes;
	int64_t total_bytes;

	if (argc < 2)
	{
		printf("Usage: %s <process_count>\n", argv[0]);
		return EINVAL;
	}

	proccess_count = atoi(argv[1]);
	if (proccess_count <= 0)
	{
		printf("Invalid proccess count: %d\n", proccess_count);
		return EINVAL;
	}

	total_count = 0;
	success_count = 0;
	time_used = 0;
	combine_stat_overall(&total_count, &success_count, &time_used);
	printf("total_count=%d, success_count=%d, success ratio: %.2f%% time_used=%ds, avg time used: %dms, QPS=%.2f\n\n", 
		total_count, success_count, total_count > 0 ? 100.00 * success_count / total_count : 0.00, 
		time_used, total_count > 0 ? time_used * 1000 / total_count : 0, 
		time_used == 0 ? 0 : (double)success_count / time_used);

	if (combine_stat_by(STAT_FILENAME_BY_FILE_TYPE, stats, FILE_TYPE_COUNT, &entry_count) == 0)
	{
		printf("file_type total_count success_count time_used(s) avg(ms) QPS success_ratio\n");
		print_stat_by(stats, entry_count);
		printf("\n");
	}

	total_bytes = 0;
	for (i=0; i<entry_count; i++)
	{
		if (strcmp(stats[i].id, "5K") == 0)
		{
			bytes = 5 * 1024;
		}
		else if (strcmp(stats[i].id, "50K") == 0)
		{
			bytes = 50 * 1024;
		}
		else if (strcmp(stats[i].id, "200K") == 0)
		{
			bytes = 200 * 1024;
		}
		else if (strcmp(stats[i].id, "1M") == 0)
		{
			bytes = 1 * 1024 * 1024;
		}
		else if (strcmp(stats[i].id, "10M") == 0)
		{
			bytes = 10 * 1024 * 1024;
		}
		else if (strcmp(stats[i].id, "100M") == 0)
		{
			bytes = 100 * 1024 * 1024;
		}
		else
		{
			bytes = 0;
		}

		total_bytes += (int64_t)bytes * stats[i].success_count;
	}
	if (time_used > 0)
	{
		printf("IO speed = %d KB\n", (int)(total_bytes / (time_used * 1024)));
	}

	if (combine_stat_by(STAT_FILENAME_BY_STORAGE_IP, stats, FILE_TYPE_COUNT, &entry_count) == 0)
	{
		printf("ip_addr  total_count success_count time_used(s) avg(ms) QPS success_ratio\n");
		print_stat_by(stats, entry_count);
		printf("\n");
	}

	return 0;
}