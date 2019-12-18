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
struct pevent {int dummy; } ;

/* Variables and functions */
 int get_common_info (struct pevent*,char const*,int*,int*) ; 
 int pevent_read_number (struct pevent*,void*,int) ; 

__attribute__((used)) static int __parse_common(struct pevent *pevent, void *data,
			  int *size, int *offset, const char *name)
{
	int ret;

	if (!*size) {
		ret = get_common_info(pevent, name, offset, size);
		if (ret < 0)
			return ret;
	}
	return pevent_read_number(pevent, data + *offset, *size);
}