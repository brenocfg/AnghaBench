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
struct nilfs_segsum_info {void* nsumblk; void* nblocks; void* nfileblk; void* sumbytes; void* nfinfo; void* next; void* ctime; void* seg_seq; int /*<<< orphan*/  flags; } ;
struct nilfs_segment_summary {int /*<<< orphan*/  ss_sumbytes; int /*<<< orphan*/  ss_nfinfo; int /*<<< orphan*/  ss_nblocks; int /*<<< orphan*/  ss_next; int /*<<< orphan*/  ss_create; int /*<<< orphan*/  ss_seq; int /*<<< orphan*/  ss_flags; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (void*,unsigned int) ; 
 int /*<<< orphan*/  NILFS_SEG_HAS_SR (struct nilfs_segsum_info*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void store_segsum_info(struct nilfs_segsum_info *ssi,
			      struct nilfs_segment_summary *sum,
			      unsigned int blocksize)
{
	ssi->flags = le16_to_cpu(sum->ss_flags);
	ssi->seg_seq = le64_to_cpu(sum->ss_seq);
	ssi->ctime = le64_to_cpu(sum->ss_create);
	ssi->next = le64_to_cpu(sum->ss_next);
	ssi->nblocks = le32_to_cpu(sum->ss_nblocks);
	ssi->nfinfo = le32_to_cpu(sum->ss_nfinfo);
	ssi->sumbytes = le32_to_cpu(sum->ss_sumbytes);

	ssi->nsumblk = DIV_ROUND_UP(ssi->sumbytes, blocksize);
	ssi->nfileblk = ssi->nblocks - ssi->nsumblk - !!NILFS_SEG_HAS_SR(ssi);
}