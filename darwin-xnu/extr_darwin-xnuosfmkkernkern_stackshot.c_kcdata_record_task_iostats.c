#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_6__* task_t ;
struct io_stats_snapshot {int /*<<< orphan*/ * ss_io_priority_size; int /*<<< orphan*/ * ss_io_priority_count; scalar_t__ ss_data_size; scalar_t__ ss_data_count; scalar_t__ ss_metadata_size; scalar_t__ ss_metadata_count; scalar_t__ ss_non_paging_size; scalar_t__ ss_non_paging_count; scalar_t__ ss_paging_size; scalar_t__ ss_paging_count; scalar_t__ ss_disk_writes_size; scalar_t__ ss_disk_writes_count; scalar_t__ ss_disk_reads_size; scalar_t__ ss_disk_reads_count; } ;
struct io_stat_info {int dummy; } ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  kcdata_descriptor_t ;
struct TYPE_12__ {scalar_t__ size; scalar_t__ count; } ;
struct TYPE_11__ {scalar_t__ size; scalar_t__ count; } ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ count; } ;
struct TYPE_9__ {scalar_t__ size; scalar_t__ count; } ;
struct TYPE_15__ {TYPE_5__* io_priority; TYPE_4__ metadata; TYPE_3__ total_io; TYPE_2__ paging; TYPE_1__ disk_reads; } ;
struct TYPE_14__ {TYPE_7__* task_io_stats; } ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int IO_NUM_PRIORITIES ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int STACKSHOT_IO_NUM_PRIORITIES ; 
 int /*<<< orphan*/  STACKSHOT_KCTYPE_IOSTATS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kcd_exit_on_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcdata_get_memory_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  memory_iszero (TYPE_7__*,int) ; 

__attribute__((used)) static kern_return_t
kcdata_record_task_iostats(kcdata_descriptor_t kcd, task_t task)
{
	kern_return_t error = KERN_SUCCESS;
	mach_vm_address_t out_addr = 0;

	/* I/O Statistics if any counters are non zero */
	assert(IO_NUM_PRIORITIES == STACKSHOT_IO_NUM_PRIORITIES);
	if (task->task_io_stats && !memory_iszero(task->task_io_stats, sizeof(struct io_stat_info))) {
		kcd_exit_on_error(kcdata_get_memory_addr(kcd, STACKSHOT_KCTYPE_IOSTATS, sizeof(struct io_stats_snapshot), &out_addr));
		struct io_stats_snapshot *_iostat = (struct io_stats_snapshot *)out_addr;
		_iostat->ss_disk_reads_count = task->task_io_stats->disk_reads.count;
		_iostat->ss_disk_reads_size = task->task_io_stats->disk_reads.size;
		_iostat->ss_disk_writes_count = (task->task_io_stats->total_io.count - task->task_io_stats->disk_reads.count);
		_iostat->ss_disk_writes_size = (task->task_io_stats->total_io.size - task->task_io_stats->disk_reads.size);
		_iostat->ss_paging_count = task->task_io_stats->paging.count;
		_iostat->ss_paging_size = task->task_io_stats->paging.size;
		_iostat->ss_non_paging_count = (task->task_io_stats->total_io.count - task->task_io_stats->paging.count);
		_iostat->ss_non_paging_size = (task->task_io_stats->total_io.size - task->task_io_stats->paging.size);
		_iostat->ss_metadata_count = task->task_io_stats->metadata.count;
		_iostat->ss_metadata_size = task->task_io_stats->metadata.size;
		_iostat->ss_data_count = (task->task_io_stats->total_io.count - task->task_io_stats->metadata.count);
		_iostat->ss_data_size = (task->task_io_stats->total_io.size - task->task_io_stats->metadata.size);
		for(int i = 0; i < IO_NUM_PRIORITIES; i++) {
			_iostat->ss_io_priority_count[i] = task->task_io_stats->io_priority[i].count;
			_iostat->ss_io_priority_size[i] = task->task_io_stats->io_priority[i].size;
		}
	}

error_exit:
	return error;
}