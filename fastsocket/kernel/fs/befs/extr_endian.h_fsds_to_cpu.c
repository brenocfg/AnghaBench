#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  max_double_indirect_range; int /*<<< orphan*/  double_indirect; int /*<<< orphan*/  max_indirect_range; int /*<<< orphan*/  indirect; int /*<<< orphan*/  max_direct_range; int /*<<< orphan*/ * direct; } ;
typedef  TYPE_1__ befs_disk_data_stream ;
struct TYPE_6__ {void* size; void* max_double_indirect_range; void* double_indirect; void* max_indirect_range; void* indirect; void* max_direct_range; void** direct; } ;
typedef  TYPE_2__ befs_data_stream ;

/* Variables and functions */
 int BEFS_NUM_DIRECT_BLOCKS ; 
 void* fs64_to_cpu (struct super_block const*,int /*<<< orphan*/ ) ; 
 void* fsrun_to_cpu (struct super_block const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline befs_data_stream
fsds_to_cpu(const struct super_block *sb, befs_disk_data_stream n)
{
	befs_data_stream data;
	int i;

	for (i = 0; i < BEFS_NUM_DIRECT_BLOCKS; ++i)
		data.direct[i] = fsrun_to_cpu(sb, n.direct[i]);

	data.max_direct_range = fs64_to_cpu(sb, n.max_direct_range);
	data.indirect = fsrun_to_cpu(sb, n.indirect);
	data.max_indirect_range = fs64_to_cpu(sb, n.max_indirect_range);
	data.double_indirect = fsrun_to_cpu(sb, n.double_indirect);
	data.max_double_indirect_range = fs64_to_cpu(sb,
						     n.
						     max_double_indirect_range);
	data.size = fs64_to_cpu(sb, n.size);

	return data;
}