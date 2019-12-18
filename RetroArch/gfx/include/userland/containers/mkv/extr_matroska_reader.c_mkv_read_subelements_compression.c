#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_17__ {size_t encodings_num; TYPE_4__* encodings; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_18__ {TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_19__ {TYPE_3__* parsing; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ data_size; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {TYPE_2__* priv; } ;
struct TYPE_14__ {TYPE_5__* module; } ;
struct TYPE_13__ {TYPE_7__* module; } ;
typedef  scalar_t__ MKV_ELEMENT_ID_T ;

/* Variables and functions */
 scalar_t__ MKV_CONTENT_ENCODING_COMPRESSION_HEADER ; 
 scalar_t__ MKV_CONTENT_ENCODING_COMPRESSION_ZLIB ; 
 scalar_t__ MKV_CONTENT_ENCODING_UNKNOWN ; 
 scalar_t__ MKV_ELEMENT_ID_CONTENT_COMPRESSION_ALGO ; 
 scalar_t__ MKV_ELEMENT_ID_CONTENT_COMPRESSION_SETTINGS ; 
 scalar_t__ MKV_MAX_ENCODING_DATA ; 
 scalar_t__ READ_BYTES (TYPE_6__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SKIP_BYTES (TYPE_6__*,scalar_t__) ; 
 scalar_t__ STREAM_STATUS (TYPE_6__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_RESOURCES ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ mkv_read_element_data_uint (TYPE_6__*,scalar_t__,int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_subelements_compression( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = module->parsing->priv->module;
   VC_CONTAINER_STATUS_T status;
   uint64_t value;
   uint8_t *data;

   if(id == MKV_ELEMENT_ID_CONTENT_COMPRESSION_ALGO)
   {
      status = mkv_read_element_data_uint(p_ctx, size, &value);
      if(status != VC_CONTAINER_SUCCESS) return status;

      if(value == 0) track_module->encodings[track_module->encodings_num].type = MKV_CONTENT_ENCODING_COMPRESSION_ZLIB;
      if(value == 3) track_module->encodings[track_module->encodings_num].type = MKV_CONTENT_ENCODING_COMPRESSION_HEADER;
      else track_module->encodings[track_module->encodings_num].type = MKV_CONTENT_ENCODING_UNKNOWN;
      return status;
   }

   if(id == MKV_ELEMENT_ID_CONTENT_COMPRESSION_SETTINGS)
   {
      if(track_module->encodings[track_module->encodings_num].type == MKV_CONTENT_ENCODING_COMPRESSION_HEADER)
      {
         if(size > MKV_MAX_ENCODING_DATA) return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;

         data = malloc((int)size);
         if(!data) return VC_CONTAINER_ERROR_OUT_OF_MEMORY;

         track_module->encodings[track_module->encodings_num].data = data;
         track_module->encodings[track_module->encodings_num].data_size = READ_BYTES(p_ctx, data, size);
         if(track_module->encodings[track_module->encodings_num].data_size != size)
            track_module->encodings[track_module->encodings_num].data_size = 0;
         return STREAM_STATUS(p_ctx);
      }
      else
      {
         SKIP_BYTES(p_ctx, size);
      }
      return STREAM_STATUS(p_ctx);
   }

   return VC_CONTAINER_SUCCESS;
}