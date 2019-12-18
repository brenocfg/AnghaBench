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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;

/* Variables and functions */
 int LZC_SEND_FLAG_COMPRESS ; 
 int LZC_SEND_FLAG_EMBED_DATA ; 
 int LZC_SEND_FLAG_LARGE_BLOCK ; 
 int /*<<< orphan*/  ZFS_IOC_SEND_NEW ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

int
lzc_send_resume(const char *snapname, const char *from, int fd,
    enum lzc_send_flags flags, uint64_t resumeobj, uint64_t resumeoff)
{
	nvlist_t *args;
	int err;

	args = fnvlist_alloc();
	fnvlist_add_int32(args, "fd", fd);
	if (from != NULL)
		fnvlist_add_string(args, "fromsnap", from);
	if (flags & LZC_SEND_FLAG_LARGE_BLOCK)
		fnvlist_add_boolean(args, "largeblockok");
	if (flags & LZC_SEND_FLAG_EMBED_DATA)
		fnvlist_add_boolean(args, "embedok");
	if (flags & LZC_SEND_FLAG_COMPRESS)
		fnvlist_add_boolean(args, "compressok");
	if (resumeobj != 0 || resumeoff != 0) {
		fnvlist_add_uint64(args, "resume_object", resumeobj);
		fnvlist_add_uint64(args, "resume_offset", resumeoff);
	}
	err = lzc_ioctl(ZFS_IOC_SEND_NEW, snapname, args, NULL);
	nvlist_free(args);
	return (err);
}