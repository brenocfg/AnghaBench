#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int x86_vendor; int x86; int x86_model; } ;

/* Variables and functions */
 int NCAPINTS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 TYPE_1__ boot_cpu_data ; 
 scalar_t__ boot_cpu_has (int) ; 
 int snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static ssize_t print_cpu_modalias(struct device *dev,
				  struct device_attribute *attr,
				  char *bufptr)
{
	int size = PAGE_SIZE;
	int i, n;
	char *buf = bufptr;

	n = snprintf(buf, size, "x86cpu:vendor:%04X:family:"
		     "%04X:model:%04X:feature:",
		boot_cpu_data.x86_vendor,
		boot_cpu_data.x86,
		boot_cpu_data.x86_model);
	size -= n;
	buf += n;
	size -= 2;
	for (i = 0; i < NCAPINTS*32; i++) {
		if (boot_cpu_has(i)) {
			n = snprintf(buf, size, ",%04X", i);
			if (n < 0) {
				WARN(1, "x86 features overflow page\n");
				break;
			}
			size -= n;
			buf += n;
		}
	}
	*buf++ = ',';
	*buf++ = '\n';
	return buf - bufptr;
}