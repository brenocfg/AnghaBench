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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_READ_U32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  MP4_SAMPLE_TABLE_CO64 ; 
 int /*<<< orphan*/  MP4_SKIP_U24 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U8 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp4_cache_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_read_box_co64( VC_CONTAINER_T *p_ctx, int64_t size )
{
   uint32_t entries;

   MP4_SKIP_U8(p_ctx, "version");
   MP4_SKIP_U24(p_ctx, "flags");

   entries = MP4_READ_U32(p_ctx, "entry_count");
   return mp4_cache_table( p_ctx, MP4_SAMPLE_TABLE_CO64, entries, size );
}