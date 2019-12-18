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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int ASF_OBJECT_HEADER_SIZE ; 
 unsigned int ASF_READ_U16 (int /*<<< orphan*/ *,int,char*) ; 
 unsigned int ASF_READ_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_BYTES (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  ASF_SKIP_GUID (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U16 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U64 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  CHECK_POINT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  asf_read_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * asf_reader_find_track (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_object_ext_stream_properties( VC_CONTAINER_T *p_ctx, int64_t size )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_TRACK_T *p_track;
   unsigned int i, name_count, pes_count, length, stream_id;

   ASF_SKIP_U64(p_ctx, size, "Start Time");
   ASF_SKIP_U64(p_ctx, size, "End Time");
   ASF_SKIP_U32(p_ctx, size, "Data Bitrate");
   ASF_SKIP_U32(p_ctx, size, "Buffer Size");
   ASF_SKIP_U32(p_ctx, size, "Initial Buffer Fullness");
   ASF_SKIP_U32(p_ctx, size, "Alternate Data Bitrate");
   ASF_SKIP_U32(p_ctx, size, "Alternate Buffer Size");
   ASF_SKIP_U32(p_ctx, size, "Alternate Initial Buffer Fullness");
   ASF_SKIP_U32(p_ctx, size, "Maximum Object Size");
   ASF_SKIP_U32(p_ctx, size, "Flags");
   stream_id = ASF_READ_U16(p_ctx, size, "Stream Number");
   ASF_SKIP_U16(p_ctx, size, "Stream Language ID Index");
   ASF_SKIP_U64(p_ctx, size, "Average Time Per Frame");
   name_count = ASF_READ_U16(p_ctx, size, "Stream Name Count");
   pes_count = ASF_READ_U16(p_ctx, size, "Payload Extension System Count");

   CHECK_POINT(p_ctx, size);

   p_track = asf_reader_find_track( p_ctx, stream_id, true);
   if(!p_track) return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;

   /* Stream Names */
   for(i = 0; i < name_count; i++)
   {
      if(size < 4) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_U16(p_ctx, size, "Language ID Index");
      length = ASF_READ_U16(p_ctx, size, "Stream Name Length");
      if(size < length) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_BYTES(p_ctx, size, length); /* Stream Name */
   }

   CHECK_POINT(p_ctx, size);

   /* Payload Extension Systems */
   for(i = 0; i < pes_count; i++)
   {
      if(size < 22) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_GUID(p_ctx, size, "Extension System ID");
      ASF_SKIP_U16(p_ctx, size, "Extension Data Size");
      length = ASF_READ_U32(p_ctx, size, "Extension System Info Length");
      if(size < length) return VC_CONTAINER_ERROR_CORRUPTED;
      ASF_SKIP_BYTES(p_ctx, size, length); /* Extension System Info */
   }

   CHECK_POINT(p_ctx, size);

   /* Optional Stream Properties Object */
   if(size >= ASF_OBJECT_HEADER_SIZE)
      status = asf_read_object(p_ctx, size);

   return status;
}