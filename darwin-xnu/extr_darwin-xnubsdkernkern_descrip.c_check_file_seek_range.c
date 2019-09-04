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
struct flock {scalar_t__ l_whence; scalar_t__ l_start; scalar_t__ l_len; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ CHECK_ADD_OVERFLOW_INT64L (scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 scalar_t__ SEEK_CUR ; 
 scalar_t__ SEEK_SET ; 

__attribute__((used)) static int
check_file_seek_range(struct flock *fl, off_t cur_file_offset)
{
	if (fl->l_whence == SEEK_CUR) {
		/* Check if the start marker is beyond LLONG_MAX. */
		if (CHECK_ADD_OVERFLOW_INT64L(fl->l_start, cur_file_offset)) {
			/* Check if start marker is negative */
			if (fl->l_start < 0) {
				return EINVAL;
			}
			return EOVERFLOW;
		}
		/* Check if the start marker is negative. */
		if (fl->l_start + cur_file_offset < 0) {
			return EINVAL;
		}
		/* Check if end marker is beyond LLONG_MAX. */
		if ((fl->l_len > 0) && (CHECK_ADD_OVERFLOW_INT64L(fl->l_start +
			cur_file_offset, fl->l_len - 1))) {
			return EOVERFLOW;
		}
		/* Check if the end marker is negative. */
		if ((fl->l_len <= 0) && (fl->l_start + cur_file_offset +
			fl->l_len < 0)) {
			return EINVAL;
		}
	} else if (fl->l_whence == SEEK_SET) {
		/* Check if the start marker is negative. */
		if (fl->l_start < 0) {
			return EINVAL;
		}
		/* Check if the end marker is beyond LLONG_MAX. */
		if ((fl->l_len > 0) &&
		    CHECK_ADD_OVERFLOW_INT64L(fl->l_start, fl->l_len - 1)) {
			return EOVERFLOW;
		}
		/* Check if the end marker is negative. */
		if ((fl->l_len < 0) &&  fl->l_start + fl->l_len < 0) {
			return EINVAL;
		}
	}
	return 0;
}