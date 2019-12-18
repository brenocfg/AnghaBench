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
typedef  int /*<<< orphan*/  u64 ;
struct readdir_data {scalar_t__ dirent; scalar_t__ used; int full; } ;
struct buffered_dirent {int namlen; unsigned int d_type; int /*<<< orphan*/  name; int /*<<< orphan*/  ino; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 unsigned int ALIGN (int,int) ; 
 int EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int nfsd_buffered_filldir(void *__buf, const char *name, int namlen,
				 loff_t offset, u64 ino, unsigned int d_type)
{
	struct readdir_data *buf = __buf;
	struct buffered_dirent *de = (void *)(buf->dirent + buf->used);
	unsigned int reclen;

	reclen = ALIGN(sizeof(struct buffered_dirent) + namlen, sizeof(u64));
	if (buf->used + reclen > PAGE_SIZE) {
		buf->full = 1;
		return -EINVAL;
	}

	de->namlen = namlen;
	de->offset = offset;
	de->ino = ino;
	de->d_type = d_type;
	memcpy(de->name, name, namlen);
	buf->used += reclen;

	return 0;
}