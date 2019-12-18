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
struct the_nilfs {scalar_t__ ns_segnum; scalar_t__ ns_nextnum; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */

__attribute__((used)) static inline int nilfs_segment_is_active(struct the_nilfs *nilfs, __u64 n)
{
	return n == nilfs->ns_segnum || n == nilfs->ns_nextnum;
}