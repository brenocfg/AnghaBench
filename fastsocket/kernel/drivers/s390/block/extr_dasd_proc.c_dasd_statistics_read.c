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
struct dasd_profile_info {int dasd_io_reqs; int dasd_io_sects; int /*<<< orphan*/  dasd_io_nr_req; int /*<<< orphan*/  dasd_io_time3; int /*<<< orphan*/  dasd_io_time2ps; int /*<<< orphan*/  dasd_io_time2; int /*<<< orphan*/  dasd_io_time1; int /*<<< orphan*/  dasd_io_timps; int /*<<< orphan*/  dasd_io_times; int /*<<< orphan*/  dasd_io_secs; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int dasd_calc_metrics (char*,char**,int /*<<< orphan*/ ,int,int*,unsigned long) ; 
 struct dasd_profile_info dasd_global_profile_data ; 
 int /*<<< orphan*/  dasd_global_profile_level ; 
 char* dasd_statistics_array (char*,int /*<<< orphan*/ ,int) ; 
 unsigned long sprintf (char*,char*,...) ; 

__attribute__((used)) static int
dasd_statistics_read(char *page, char **start, off_t off,
		     int count, int *eof, void *data)
{
	unsigned long len;
#ifdef CONFIG_DASD_PROFILE
	struct dasd_profile_info *prof;
	char *str;
	int factor;

	/* check for active profiling */
	if (!dasd_global_profile_level) {
		len = sprintf(page, "Statistics are off - they might be "
				    "switched on using 'echo set on > "
				    "/proc/dasd/statistics'\n");
		return dasd_calc_metrics(page, start, off, count, eof, len);
	}
	prof = &dasd_global_profile_data;

	/* prevent couter 'overflow' on output */
	for (factor = 1; (prof->dasd_io_reqs / factor) > 9999999;
	     factor *= 10);

	str = page;
	str += sprintf(str, "%d dasd I/O requests\n", prof->dasd_io_reqs);
	str += sprintf(str, "with %u sectors(512B each)\n",
		       prof->dasd_io_sects);
	str += sprintf(str, "Scale Factor is  %d\n", factor);
	str += sprintf(str,
		       "   __<4	   ___8	   __16	   __32	   __64	   _128	"
		       "   _256	   _512	   __1k	   __2k	   __4k	   __8k	"
		       "   _16k	   _32k	   _64k	   128k\n");
	str += sprintf(str,
		       "   _256	   _512	   __1M	   __2M	   __4M	   __8M	"
		       "   _16M	   _32M	   _64M	   128M	   256M	   512M	"
		       "   __1G	   __2G	   __4G " "   _>4G\n");

	str += sprintf(str, "Histogram of sizes (512B secs)\n");
	str = dasd_statistics_array(str, prof->dasd_io_secs, factor);
	str += sprintf(str, "Histogram of I/O times (microseconds)\n");
	str = dasd_statistics_array(str, prof->dasd_io_times, factor);
	str += sprintf(str, "Histogram of I/O times per sector\n");
	str = dasd_statistics_array(str, prof->dasd_io_timps, factor);
	str += sprintf(str, "Histogram of I/O time till ssch\n");
	str = dasd_statistics_array(str, prof->dasd_io_time1, factor);
	str += sprintf(str, "Histogram of I/O time between ssch and irq\n");
	str = dasd_statistics_array(str, prof->dasd_io_time2, factor);
	str += sprintf(str, "Histogram of I/O time between ssch "
			    "and irq per sector\n");
	str = dasd_statistics_array(str, prof->dasd_io_time2ps, factor);
	str += sprintf(str, "Histogram of I/O time between irq and end\n");
	str = dasd_statistics_array(str, prof->dasd_io_time3, factor);
	str += sprintf(str, "# of req in chanq at enqueuing (1..32) \n");
	str = dasd_statistics_array(str, prof->dasd_io_nr_req, factor);
	len = str - page;
#else
	len = sprintf(page, "Statistics are not activated in this kernel\n");
#endif
	return dasd_calc_metrics(page, start, off, count, eof, len);
}