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
typedef  scalar_t__ u64 ;
typedef  unsigned int u32 ;
struct gfs2_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_addr; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_type; TYPE_1__ de_inum; int /*<<< orphan*/  de_name_len; int /*<<< orphan*/  de_hash; } ;
typedef  int (* filldir_t ) (void*,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_dents ; 
 scalar_t__ gfs2_disk_hash2offset (scalar_t__) ; 
 int /*<<< orphan*/  sort (struct gfs2_dirent const**,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_filldir_main(struct gfs2_inode *dip, u64 *offset,
			   void *opaque, filldir_t filldir,
			   const struct gfs2_dirent **darr, u32 entries,
			   int *copied)
{
	const struct gfs2_dirent *dent, *dent_next;
	u64 off, off_next;
	unsigned int x, y;
	int run = 0;
	int error = 0;

	sort(darr, entries, sizeof(struct gfs2_dirent *), compare_dents, NULL);

	dent_next = darr[0];
	off_next = be32_to_cpu(dent_next->de_hash);
	off_next = gfs2_disk_hash2offset(off_next);

	for (x = 0, y = 1; x < entries; x++, y++) {
		dent = dent_next;
		off = off_next;

		if (y < entries) {
			dent_next = darr[y];
			off_next = be32_to_cpu(dent_next->de_hash);
			off_next = gfs2_disk_hash2offset(off_next);

			if (off < *offset)
				continue;
			*offset = off;

			if (off_next == off) {
				if (*copied && !run)
					return 1;
				run = 1;
			} else
				run = 0;
		} else {
			if (off < *offset)
				continue;
			*offset = off;
		}

		error = filldir(opaque, (const char *)(dent + 1),
				be16_to_cpu(dent->de_name_len),
				off, be64_to_cpu(dent->de_inum.no_addr),
				be16_to_cpu(dent->de_type));
		if (error)
			return 1;

		*copied = 1;
	}

	/* Increment the *offset by one, so the next time we come into the
	   do_filldir fxn, we get the next entry instead of the last one in the
	   current leaf */

	(*offset)++;

	return 0;
}