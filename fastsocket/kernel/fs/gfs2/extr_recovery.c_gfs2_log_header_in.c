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
struct gfs2_log_header_host {void* lh_hash; void* lh_blkno; void* lh_tail; void* lh_flags; int /*<<< orphan*/  lh_sequence; } ;
struct TYPE_2__ {scalar_t__ mh_magic; scalar_t__ mh_type; } ;
struct gfs2_log_header {int /*<<< orphan*/  lh_hash; int /*<<< orphan*/  lh_blkno; int /*<<< orphan*/  lh_tail; int /*<<< orphan*/  lh_flags; int /*<<< orphan*/  lh_sequence; TYPE_1__ lh_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  GFS2_METATYPE_LH ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_log_header_in(struct gfs2_log_header_host *lh, const void *buf)
{
	const struct gfs2_log_header *str = buf;

	if (str->lh_header.mh_magic != cpu_to_be32(GFS2_MAGIC) ||
	    str->lh_header.mh_type != cpu_to_be32(GFS2_METATYPE_LH))
		return 1;

	lh->lh_sequence = be64_to_cpu(str->lh_sequence);
	lh->lh_flags = be32_to_cpu(str->lh_flags);
	lh->lh_tail = be32_to_cpu(str->lh_tail);
	lh->lh_blkno = be32_to_cpu(str->lh_blkno);
	lh->lh_hash = be32_to_cpu(str->lh_hash);
	return 0;
}