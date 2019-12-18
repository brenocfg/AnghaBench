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
typedef  int u64 ;
typedef  int s64 ;

/* Variables and functions */
 char* feature_set_info (char*,int,int,int,int) ; 
 int ia64_pal_proc_get_features (int*,int*,int*,int) ; 

__attribute__((used)) static int
processor_info(char *page)
{
	char *p = page;
	u64 avail=1, status=1, control=1, feature_set=0;
	s64 ret;

	do {
		ret = ia64_pal_proc_get_features(&avail, &status, &control,
						feature_set);
		if (ret < 0) {
			return p - page;
		}
		if (ret == 1) {
			feature_set++;
			continue;
		}

		p = feature_set_info(p, avail, status, control, feature_set);

		feature_set++;
	} while(1);

	return p - page;
}