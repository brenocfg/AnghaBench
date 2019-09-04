#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  total_uncompressed_pages_in_compressor; int /*<<< orphan*/  compressor_page_count; int /*<<< orphan*/  decompressions; int /*<<< orphan*/  compressions; int /*<<< orphan*/  internal_page_count; int /*<<< orphan*/  external_page_count; int /*<<< orphan*/  speculative_count; int /*<<< orphan*/  wire_count; int /*<<< orphan*/  purgeable_count; int /*<<< orphan*/  throttled_count; int /*<<< orphan*/  inactive_count; int /*<<< orphan*/  active_count; int /*<<< orphan*/  free_count; } ;
typedef  TYPE_1__ vm_statistics64_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  largest_zone_size; int /*<<< orphan*/  largest_zone_name; int /*<<< orphan*/  zone_map_capacity; int /*<<< orphan*/  zone_map_size; int /*<<< orphan*/  total_uncompressed_pages_in_compressor; int /*<<< orphan*/  compressor_pages; int /*<<< orphan*/  decompressions; int /*<<< orphan*/  compressions; int /*<<< orphan*/  anonymous_pages; int /*<<< orphan*/  filebacked_pages; int /*<<< orphan*/  speculative_pages; int /*<<< orphan*/  wired_pages; int /*<<< orphan*/  purgeable_pages; int /*<<< orphan*/  throttled_pages; int /*<<< orphan*/  inactive_pages; int /*<<< orphan*/  active_pages; int /*<<< orphan*/  free_pages; } ;
struct TYPE_6__ {TYPE_3__ stats; } ;
typedef  TYPE_2__ memorystatus_jetsam_snapshot_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int kern_return_t ;
typedef  int /*<<< orphan*/  host_info64_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_VM_INFO64 ; 
 int /*<<< orphan*/  HOST_VM_INFO64_COUNT ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  get_largest_zone_info (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_zone_map_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_self () ; 
 int host_statistics64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
memorystatus_init_snapshot_vmstats(memorystatus_jetsam_snapshot_t *snapshot)
{
	kern_return_t kr = KERN_SUCCESS;
	mach_msg_type_number_t	count = HOST_VM_INFO64_COUNT;
	vm_statistics64_data_t	vm_stat;

	if ((kr = host_statistics64(host_self(), HOST_VM_INFO64, (host_info64_t)&vm_stat, &count)) != KERN_SUCCESS) {
		printf("memorystatus_init_jetsam_snapshot_stats: host_statistics64 failed with %d\n", kr);
		memset(&snapshot->stats, 0, sizeof(snapshot->stats));
	} else {
		snapshot->stats.free_pages	= vm_stat.free_count;
		snapshot->stats.active_pages	= vm_stat.active_count;
		snapshot->stats.inactive_pages	= vm_stat.inactive_count;
		snapshot->stats.throttled_pages	= vm_stat.throttled_count;
		snapshot->stats.purgeable_pages	= vm_stat.purgeable_count;
		snapshot->stats.wired_pages	= vm_stat.wire_count;

		snapshot->stats.speculative_pages = vm_stat.speculative_count;
		snapshot->stats.filebacked_pages  = vm_stat.external_page_count;
		snapshot->stats.anonymous_pages   = vm_stat.internal_page_count;
		snapshot->stats.compressions      = vm_stat.compressions;
		snapshot->stats.decompressions    = vm_stat.decompressions;
		snapshot->stats.compressor_pages  = vm_stat.compressor_page_count;
		snapshot->stats.total_uncompressed_pages_in_compressor = vm_stat.total_uncompressed_pages_in_compressor;
	}

	get_zone_map_size(&snapshot->stats.zone_map_size, &snapshot->stats.zone_map_capacity);
	get_largest_zone_info(snapshot->stats.largest_zone_name, sizeof(snapshot->stats.largest_zone_name),
			&snapshot->stats.largest_zone_size);
}