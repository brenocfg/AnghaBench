#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {TYPE_2__* sample_table; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {TYPE_1__* sample_table; } ;
struct TYPE_8__ {int entries; int entry_size; scalar_t__ offset; } ;
struct TYPE_7__ {int entry; } ;
typedef  size_t MP4_SAMPLE_TABLE_T ;
typedef  TYPE_4__ MP4_READER_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_seek_sample_table( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_MODULE_T *track_module, MP4_READER_STATE_T *state,
   MP4_SAMPLE_TABLE_T table)
{
   int64_t seek_offset;

   /* Seek to the next entry in the table */
   if(state->sample_table[table].entry >= track_module->sample_table[table].entries)
      return VC_CONTAINER_ERROR_EOS;

   seek_offset = track_module->sample_table[table].offset +
      track_module->sample_table[table].entry_size * state->sample_table[table].entry;

   return SEEK(p_ctx, seek_offset);
}