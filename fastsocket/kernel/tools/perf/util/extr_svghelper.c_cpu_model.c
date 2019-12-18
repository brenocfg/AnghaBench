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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 unsigned int max_freq ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 unsigned int strtoull (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *cpu_model(void)
{
	static char cpu_m[255];
	char buf[256];
	FILE *file;

	cpu_m[0] = 0;
	/* CPU type */
	file = fopen("/proc/cpuinfo", "r");
	if (file) {
		while (fgets(buf, 255, file)) {
			if (strstr(buf, "model name")) {
				strncpy(cpu_m, &buf[13], 255);
				break;
			}
		}
		fclose(file);
	}

	/* CPU type */
	file = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies", "r");
	if (file) {
		while (fgets(buf, 255, file)) {
			unsigned int freq;
			freq = strtoull(buf, NULL, 10);
			if (freq > max_freq)
				max_freq = freq;
		}
		fclose(file);
	}
	return cpu_m;
}