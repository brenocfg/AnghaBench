#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_22__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_19__ {scalar_t__ output_format; scalar_t__ render_format; TYPE_4__ render_rect; TYPE_4__ output_rect; scalar_t__ tunnelling; } ;
struct TYPE_25__ {size_t connection_num; TYPE_1__ options; TYPE_5__* converter_out_port; TYPE_5__* video_out_port; TYPE_6__** connection; } ;
struct TYPE_24__ {void* user_data; int /*<<< orphan*/  callback; } ;
struct TYPE_23__ {TYPE_15__* format; int /*<<< orphan*/  name; } ;
struct TYPE_20__ {scalar_t__ height; scalar_t__ width; TYPE_4__ crop; } ;
struct TYPE_21__ {TYPE_2__ video; } ;
struct TYPE_18__ {scalar_t__ encoding; TYPE_3__* es; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_RECT_T ;
typedef  TYPE_5__ MMAL_PORT_T ;
typedef  TYPE_6__ MMAL_CONNECTION_T ;
typedef  scalar_t__ MMAL_BOOL_T ;
typedef  TYPE_7__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 scalar_t__ MMAL_CONNECTION_FLAG_TUNNELLING ; 
 size_t MMAL_COUNTOF (TYPE_6__**) ; 
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 scalar_t__ MMAL_ENOMEM ; 
 scalar_t__ MMAL_FALSE ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ MMAL_TRUE ; 
 int /*<<< orphan*/  log_format (TYPE_15__*,TYPE_5__*) ; 
 scalar_t__ mmal_connection_create (TYPE_6__**,TYPE_5__*,TYPE_5__*,scalar_t__) ; 
 scalar_t__ mmal_port_format_commit (TYPE_5__*) ; 
 int /*<<< orphan*/  mmalplay_connection_cb ; 

__attribute__((used)) static MMAL_STATUS_T mmalplay_connection_create(MMALPLAY_T *ctx, MMAL_PORT_T *out, MMAL_PORT_T *in, uint32_t flags)
{
   MMAL_CONNECTION_T **connection = &ctx->connection[ctx->connection_num];
   uint32_t encoding_override = MMAL_ENCODING_UNKNOWN;
   MMAL_RECT_T *rect_override = NULL;
   MMAL_BOOL_T format_override = MMAL_FALSE;
   MMAL_STATUS_T status;

   if (ctx->connection_num >= MMAL_COUNTOF(ctx->connection))
      return MMAL_ENOMEM;

   /* Globally enable tunnelling if requested by the user */
   flags |= ctx->options.tunnelling ? MMAL_CONNECTION_FLAG_TUNNELLING : 0;

   /* Apply any override to the format specified by the user */
   if (out == ctx->video_out_port)
   {
      encoding_override = ctx->options.output_format;
      rect_override = &ctx->options.output_rect;
   }
   else if (out == ctx->converter_out_port)
   {
      encoding_override = ctx->options.render_format;
      rect_override = &ctx->options.render_rect;
   }

   if (encoding_override != MMAL_ENCODING_UNKNOWN &&
       encoding_override != out->format->encoding)
   {
      out->format->encoding = encoding_override;
      format_override = MMAL_TRUE;
   }

   if (rect_override && rect_override->width && rect_override->height)
   {
      out->format->es->video.crop = *rect_override;
      out->format->es->video.width = rect_override->width;
      out->format->es->video.height = rect_override->height;
      format_override = MMAL_TRUE;
   }

   if (format_override)
   {
      status = mmal_port_format_commit(out);
      if (status != MMAL_SUCCESS)
      {
         LOG_ERROR("cannot override format on output port %s", out->name);
         return status;
      }
   }

   /* Create the actual connection */
   status = mmal_connection_create(connection, out, in, flags);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("cannot create connection");
      return status;
   }

   /* Set our connection callback */
   (*connection)->callback = mmalplay_connection_cb;
   (*connection)->user_data = (void *)ctx;

   log_format(out->format, out);
   log_format(in->format, in);

   ctx->connection_num++;
   return MMAL_SUCCESS;
}