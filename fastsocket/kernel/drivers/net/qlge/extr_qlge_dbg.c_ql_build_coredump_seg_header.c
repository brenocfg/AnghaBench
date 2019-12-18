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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct mpi_coredump_segment_header {int /*<<< orphan*/  description; void* segSize; void* segNum; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_COREDUMP_COOKIE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct mpi_coredump_segment_header*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ql_build_coredump_seg_header(
		struct mpi_coredump_segment_header *seg_hdr,
		u32 seg_number, u32 seg_size, u8 *desc)
{
	memset(seg_hdr, 0, sizeof(struct mpi_coredump_segment_header));
	seg_hdr->cookie = MPI_COREDUMP_COOKIE;
	seg_hdr->segNum = seg_number;
	seg_hdr->segSize = seg_size;
	memcpy(seg_hdr->description, desc, (sizeof(seg_hdr->description)) - 1);
}