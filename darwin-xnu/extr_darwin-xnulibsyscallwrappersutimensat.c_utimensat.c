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
typedef  int /*<<< orphan*/  times_in ;
struct timespec {int dummy; } ;
struct attrlist {int /*<<< orphan*/  commonattr; int /*<<< orphan*/  bitmapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_BIT_MAP_COUNT ; 
 int AT_SYMLINK_NOFOLLOW ; 
 int FSOPT_NOFOLLOW ; 
 int /*<<< orphan*/  memcpy (struct timespec**,struct timespec const*,int) ; 
 int /*<<< orphan*/  prepare_times_array_and_attrs (struct timespec*,struct timespec*,size_t*) ; 
 int setattrlistat (int,char const*,struct attrlist*,struct timespec**,size_t,int) ; 
 struct timespec const* times_now ; 

int
utimensat(int fd, const char *path, const struct timespec _times_in[2], int flags)
{
	struct timespec times_in[2];
	if (_times_in != NULL) {
		memcpy(&times_in, _times_in, sizeof(times_in));
	} else {
		memcpy(&times_in, times_now, sizeof(times_in));
	}

	size_t attrbuf_size = 0;
	struct timespec times_out[2] = {};
	struct attrlist a = {
		.bitmapcount = ATTR_BIT_MAP_COUNT
	};
	a.commonattr = prepare_times_array_and_attrs(times_in, times_out, &attrbuf_size);

	int flags_out = 0;
	if (flags & AT_SYMLINK_NOFOLLOW) {
		flags_out |= FSOPT_NOFOLLOW;
	}

	return setattrlistat(fd, path, &a, &times_out, attrbuf_size, flags_out);
}