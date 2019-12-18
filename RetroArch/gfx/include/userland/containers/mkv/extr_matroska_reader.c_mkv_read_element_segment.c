#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {TYPE_1__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {int level; TYPE_2__* levels; } ;
struct TYPE_14__ {int timecode_scale; double duration; int /*<<< orphan*/  element_level; TYPE_3__ state; int /*<<< orphan*/  element_offset; int /*<<< orphan*/  cluster_offset; scalar_t__ segment_size; scalar_t__ segment_offset; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_11__ {scalar_t__ data_offset; scalar_t__ data_start; scalar_t__ id; scalar_t__ size; scalar_t__ offset; } ;
struct TYPE_10__ {TYPE_5__* module; } ;
typedef  int /*<<< orphan*/  MKV_ELEMENT_T ;
typedef  scalar_t__ MKV_ELEMENT_ID_T ;

/* Variables and functions */
 scalar_t__ MKV_ELEMENT_ID_CLUSTER ; 
 scalar_t__ MKV_ELEMENT_ID_SEGMENT ; 
 scalar_t__ MKV_ELEMENT_MIN_HEADER_SIZE ; 
 scalar_t__ STREAM_POSITION (TYPE_4__*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/ * mkv_elements_list ; 
 scalar_t__ mkv_read_element_data (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ mkv_read_element_header (TYPE_4__*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_element_segment( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   int64_t offset = STREAM_POSITION(p_ctx);
   bool unknown_size = size < 0;

   /* Read contained elements */
   /* Initialise state used by reader */
   module->state.level = 0;
   module->state.levels[0].offset = STREAM_POSITION(p_ctx);
   module->state.levels[0].size = size;
   module->state.levels[0].id = MKV_ELEMENT_ID_SEGMENT;
   module->state.levels[0].data_start = 0;
   module->state.levels[0].data_offset = 0;
   module->timecode_scale = 1000000;
   module->duration = 0.0;
   module->segment_offset = STREAM_POSITION(p_ctx);
   module->segment_size = size;

   /* Read contained elements until we have all the information we need to start
    * playing the stream */
   module->element_level++;
   while(status == VC_CONTAINER_SUCCESS &&
         (unknown_size || size >= MKV_ELEMENT_MIN_HEADER_SIZE))
   {
      MKV_ELEMENT_T *child = mkv_elements_list;
      MKV_ELEMENT_ID_T child_id;
      int64_t child_size;

      offset = STREAM_POSITION(p_ctx);

      status = mkv_read_element_header(p_ctx, size, &child_id, &child_size, id, &child);
      if(status != VC_CONTAINER_SUCCESS) break;

      if(child_id == MKV_ELEMENT_ID_CLUSTER)
      {
         /* We found the start of the data */
         module->cluster_offset = module->element_offset;
         module->state.level = 1;
         module->state.levels[1].offset = STREAM_POSITION(p_ctx);
         module->state.levels[1].size = child_size;
         module->state.levels[1].id = MKV_ELEMENT_ID_CLUSTER;
         module->state.levels[1].data_start = 0;
         module->state.levels[1].data_offset = 0;
         break;
      }

      status = mkv_read_element_data(p_ctx, child, child_size, size);
      if(!unknown_size) size -= (STREAM_POSITION(p_ctx) - offset);
   }

   module->element_level--;
   return status;
}