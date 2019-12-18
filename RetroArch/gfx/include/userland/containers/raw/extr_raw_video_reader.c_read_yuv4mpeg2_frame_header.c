#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
struct TYPE_11__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {unsigned int block_size; int frame_header_size; int /*<<< orphan*/  option; scalar_t__ non_standard; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_10__ {TYPE_3__* module; } ;

/* Variables and functions */
 int FRAME_HEADER_SIZE_MAX ; 
 int /*<<< orphan*/  LOG_ERROR (TYPE_2__*,char*) ; 
 int READ_BYTES (TYPE_2__*,char*,int) ; 
 scalar_t__ STREAM_STATUS (TYPE_2__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_CORRUPTED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int _READ_U8 (TYPE_2__*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ read_yuv4mpeg2_option (TYPE_2__*,unsigned int*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T read_yuv4mpeg2_frame_header( VC_CONTAINER_T *ctx )
{
   VC_CONTAINER_MODULE_T *module = ctx->priv->module;
   unsigned int bytes_left = FRAME_HEADER_SIZE_MAX - 5;
   unsigned int value1;
   char header[5];

   if (READ_BYTES(ctx, header, sizeof(header)) != sizeof(header) ||
          memcmp(header, "FRAME", sizeof(header)))
   {
      LOG_ERROR(ctx, "missing frame marker");
      return STREAM_STATUS(ctx) != VC_CONTAINER_SUCCESS ?
         STREAM_STATUS(ctx) : VC_CONTAINER_ERROR_CORRUPTED;
   }

   /* Parse parameters */
   while (read_yuv4mpeg2_option(ctx, &bytes_left) == VC_CONTAINER_SUCCESS)
   {
      if (module->non_standard && sscanf(module->option, "S%i", &value1) == 1)
         module->block_size = value1;
   }

   /* Check the end marker */
   if (_READ_U8(ctx) != 0x0a)
   {
      LOG_ERROR(ctx, "missing end of frame header marker");
      return VC_CONTAINER_ERROR_CORRUPTED;
   }

   module->frame_header_size = FRAME_HEADER_SIZE_MAX - bytes_left - 1;
   return VC_CONTAINER_SUCCESS;
}