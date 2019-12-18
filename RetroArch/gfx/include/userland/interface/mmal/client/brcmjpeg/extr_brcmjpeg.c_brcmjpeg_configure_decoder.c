#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ output_handle; int /*<<< orphan*/  pixel_format; } ;
struct TYPE_20__ {TYPE_1__* mmal; scalar_t__ slice_height; } ;
struct TYPE_19__ {int buffer_num; TYPE_5__* format; scalar_t__ is_enabled; } ;
struct TYPE_18__ {TYPE_4__* es; scalar_t__ encoding; } ;
struct TYPE_15__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_16__ {scalar_t__ height; scalar_t__ width; TYPE_2__ crop; } ;
struct TYPE_17__ {TYPE_3__ video; } ;
struct TYPE_14__ {TYPE_6__** output; void* status; } ;
typedef  void* MMAL_STATUS_T ;
typedef  TYPE_6__ MMAL_PORT_T ;
typedef  scalar_t__ MMAL_FOURCC_T ;
typedef  TYPE_7__ BRCMJPEG_T ;
typedef  int /*<<< orphan*/  BRCMJPEG_STATUS_T ;
typedef  TYPE_8__ BRCMJPEG_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMJPEG_SUCCESS ; 
 int /*<<< orphan*/  CHECK_MMAL_STATUS (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXECUTE ; 
 int /*<<< orphan*/  LOG_DEBUG (char*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 void* MMAL_EINVAL ; 
 scalar_t__ MMAL_ENCODING_I420 ; 
 scalar_t__ MMAL_ENCODING_I422 ; 
 scalar_t__ MMAL_ENCODING_RGBA ; 
 void* MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_WRAPPER_FLAG_PAYLOAD_ALLOCATE ; 
 int /*<<< orphan*/  MMAL_WRAPPER_FLAG_PAYLOAD_USE_SHARED_MEMORY ; 
 int /*<<< orphan*/  OUTPUT_FORMAT ; 
 scalar_t__ brcmjpeg_pixfmt_to_encoding (int /*<<< orphan*/ ) ; 
 void* mmal_port_format_commit (TYPE_6__*) ; 
 void* mmal_wrapper_port_disable (TYPE_6__*) ; 
 void* mmal_wrapper_port_enable (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BRCMJPEG_STATUS_T brcmjpeg_configure_decoder(BRCMJPEG_T *ctx,
   BRCMJPEG_REQUEST_T *req)
{
   MMAL_STATUS_T status = MMAL_SUCCESS;
   MMAL_FOURCC_T encoding = brcmjpeg_pixfmt_to_encoding(req->pixel_format);
   MMAL_PORT_T *port_out;
   BRCMJPEG_STATUS_T err = BRCMJPEG_SUCCESS;

   if (encoding != MMAL_ENCODING_I420 &&
       encoding != MMAL_ENCODING_I422 &&
       encoding != MMAL_ENCODING_RGBA)
      status = MMAL_EINVAL;
   CHECK_MMAL_STATUS(status, OUTPUT_FORMAT, "format not supported");

   ctx->slice_height = 0;
   ctx->mmal->status = MMAL_SUCCESS;
   port_out = ctx->mmal->output[0];

   /* The input port needs to be re-configured to take into account
    * the properties of the new frame to decode */
   if (port_out->is_enabled)
   {
       status = mmal_wrapper_port_disable(port_out);
       CHECK_MMAL_STATUS(status, EXECUTE, "failed to disable output port");
   }

   /* We assume that we do not know the format of the new jpeg to be decoded
    * and configure the input port for autodetecting the new format */
   port_out->format->encoding = encoding;
   port_out->format->es->video.width =
      port_out->format->es->video.crop.width = 0;
   port_out->format->es->video.height =
      port_out->format->es->video.crop.height = 0;
   status = mmal_port_format_commit(port_out);
   CHECK_MMAL_STATUS(status, OUTPUT_FORMAT, "failed to commit output port format");

   port_out->buffer_num = 1;
   if (req->output_handle)
      status = mmal_wrapper_port_enable(port_out, MMAL_WRAPPER_FLAG_PAYLOAD_USE_SHARED_MEMORY);
   else
      status = mmal_wrapper_port_enable(port_out, MMAL_WRAPPER_FLAG_PAYLOAD_ALLOCATE);
   CHECK_MMAL_STATUS(status, EXECUTE, "failed to enable output port");

   LOG_DEBUG("decoder configured (%4.4s:%ux%u|%ux%u)", (char *)&port_out->format->encoding,
         port_out->format->es->video.crop.width, port_out->format->es->video.crop.height,
         port_out->format->es->video.width, port_out->format->es->video.height);
   return BRCMJPEG_SUCCESS;

 error:
   return err;
}