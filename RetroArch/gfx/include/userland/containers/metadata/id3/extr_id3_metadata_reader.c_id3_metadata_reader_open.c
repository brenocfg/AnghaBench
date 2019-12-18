#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_15__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_14__ {int /*<<< orphan*/  pf_close; TYPE_1__* io; } ;
struct TYPE_13__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ INT64_C (int) ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int PEEK_BYTES (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  SEEK (TYPE_3__*,scalar_t__) ; 
 scalar_t__ STREAM_POSITION (TYPE_3__*) ; 
 scalar_t__ STREAM_SEEKABLE (TYPE_3__*) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_3__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  id3_metadata_reader_close ; 
 int /*<<< orphan*/  id3_read_id3v1_tag (TYPE_3__*) ; 
 int /*<<< orphan*/  id3_read_id3v2_tag (TYPE_3__*) ; 

VC_CONTAINER_STATUS_T id3_metadata_reader_open( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_INVALID;
   uint8_t peek_buf[10];
   int64_t data_offset;

   if (PEEK_BYTES(p_ctx, peek_buf, 10) != 10)
     return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Initial ID3v2 tag(s), variable size */
   while ((peek_buf[0] == 'I') && (peek_buf[1] == 'D') && (peek_buf[2] == '3'))
   {
      if ((status = id3_read_id3v2_tag(p_ctx)) != VC_CONTAINER_SUCCESS)
      {
         LOG_DEBUG(p_ctx, "error reading ID3v2 tag (%i)", status);
      }

      if (PEEK_BYTES(p_ctx, peek_buf, 10) != 10) break;
   }

   data_offset = STREAM_POSITION(p_ctx);

   /* ID3v1 tag, 128 bytes at the end of a file */
   if (p_ctx->priv->io->size >= INT64_C(128) && STREAM_SEEKABLE(p_ctx))
   {
      SEEK(p_ctx, p_ctx->priv->io->size - INT64_C(128));
      if (PEEK_BYTES(p_ctx, peek_buf, 3) != 3) goto end;

      if ((peek_buf[0] == 'T') && (peek_buf[1] == 'A') && (peek_buf[2] == 'G'))
      {
         if ((status = id3_read_id3v1_tag(p_ctx)) != VC_CONTAINER_SUCCESS)
         {
            LOG_DEBUG(p_ctx, "error reading ID3v1 tag (%i)", status);
         }
      }
   }

end:
   /* Restore position to start of data */
   if (STREAM_POSITION(p_ctx) != data_offset)
      SEEK(p_ctx, data_offset);

   p_ctx->priv->pf_close = id3_metadata_reader_close;

   if((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS) goto error;

   return VC_CONTAINER_SUCCESS;

error:
   LOG_DEBUG(p_ctx, "error opening stream (%i)", status);
   return status;
}