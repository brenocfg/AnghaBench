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
typedef  int uint16_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int ASF_READ_U16 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U16 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_object_stream_bitrate_props( VC_CONTAINER_T *p_ctx, int64_t size )
{
   uint16_t i, count;

   count = ASF_READ_U16(p_ctx, size, "Bitrate Records Count");

   /* Bitrate records */
   if(size < count * 6) return VC_CONTAINER_ERROR_CORRUPTED;
   for(i = 0; i < count; i++)
   {
      ASF_SKIP_U16(p_ctx, size, "Flags");
      ASF_SKIP_U32(p_ctx, size, "Average Bitrate");
   }

   return STREAM_STATUS(p_ctx);
}