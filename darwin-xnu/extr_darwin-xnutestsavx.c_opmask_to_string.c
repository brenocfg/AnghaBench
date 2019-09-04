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
typedef  int /*<<< orphan*/  OPMASK ;

/* Variables and functions */
 unsigned int KARRAY_MAX ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int sprintf (char*,char*,unsigned int,int /*<<< orphan*/ ,char*) ; 

void
opmask_to_string(OPMASK *karray, char *buf) {
	unsigned int karray_idx = 0;
	unsigned int buf_idx = 0;
	int ret = 0;

	for(karray_idx = 0; karray_idx < KARRAY_MAX; karray_idx++) {
		ret = sprintf(
			buf + buf_idx,
			"k%d: 0x%016llx%s",
			karray_idx, karray[karray_idx],
			karray_idx < KARRAY_MAX ? "\n" : ""
		);
		T_QUIET; T_ASSERT_POSIX_SUCCESS(ret, "sprintf()");
		buf_idx += ret;
	}
}