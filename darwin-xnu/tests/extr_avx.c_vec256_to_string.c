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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  a ;
typedef  int /*<<< orphan*/  VECTOR256 ;

/* Variables and functions */
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 unsigned int YMM_MAX ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vec256_to_string(VECTOR256 *vec, char *buf) {
	unsigned int vec_idx = 0;
	unsigned int buf_idx = 0;
	int ret = 0;

	for (vec_idx = 0; vec_idx < YMM_MAX; vec_idx++) {
		uint64_t a[4];
		bcopy(&vec[vec_idx], &a[0], sizeof(a));
		ret = sprintf(
			buf + buf_idx,
			"0x%016llx:%016llx:%016llx:%016llx\n",
			a[0], a[1], a[2], a[3]
		);
		T_QUIET; T_ASSERT_POSIX_SUCCESS(ret, "sprintf()");
		buf_idx += ret;
	}
}