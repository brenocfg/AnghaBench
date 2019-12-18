#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ xfs_dir2_data_unused_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __be16 *
xfs_dir2_data_unused_tag_p(xfs_dir2_data_unused_t *dup)
{
	return (__be16 *)((char *)dup +
			be16_to_cpu(dup->length) - sizeof(__be16));
}