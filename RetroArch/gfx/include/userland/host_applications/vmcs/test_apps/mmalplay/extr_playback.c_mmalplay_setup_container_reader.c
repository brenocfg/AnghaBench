#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_19__ {int seeking; } ;
struct TYPE_23__ {int is_still_image; TYPE_3__ options; TYPE_2__* reader_audio; TYPE_2__* reader_video; } ;
struct TYPE_22__ {unsigned int output_num; int name; int /*<<< orphan*/  control; TYPE_2__** output; } ;
struct TYPE_15__ {unsigned int size; int /*<<< orphan*/  id; } ;
struct TYPE_17__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int offset; TYPE_10__ hdr; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_20__ {TYPE_10__ hdr; int /*<<< orphan*/  str; } ;
struct TYPE_18__ {TYPE_13__* format; } ;
struct TYPE_16__ {scalar_t__ type; scalar_t__ encoding; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PARAMETER_STRING_T ;
typedef  TYPE_5__ MMAL_PARAMETER_SEEK_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;
typedef  TYPE_7__ MMALPLAY_T ;

/* Variables and functions */
 int INT64_C (int) ; 
 int /*<<< orphan*/  LOG_DEBUG (char*,int) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  LOG_INFO (char*) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENCODING_BMP ; 
 scalar_t__ MMAL_ENCODING_GIF ; 
 scalar_t__ MMAL_ENCODING_JPEG ; 
 scalar_t__ MMAL_ENCODING_PNG ; 
 scalar_t__ MMAL_ENCODING_PPM ; 
 scalar_t__ MMAL_ENCODING_TGA ; 
 scalar_t__ MMAL_ENOMEM ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_ES_TYPE_AUDIO ; 
 scalar_t__ MMAL_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  MMAL_PARAMETER_SEEK ; 
 int /*<<< orphan*/  MMAL_PARAMETER_URI ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  log_format (TYPE_13__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ mmal_port_parameter_set (int /*<<< orphan*/ ,TYPE_10__*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  vcos_safe_strcpy (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmalplay_setup_container_reader(MMALPLAY_T *ctx,
   MMAL_COMPONENT_T *reader, const char *uri)
{
   MMAL_PARAMETER_SEEK_T seek = {{MMAL_PARAMETER_SEEK, sizeof(MMAL_PARAMETER_SEEK_T)},0,0};
   MMAL_PARAMETER_STRING_T *param = 0;
   unsigned int param_size, track_audio, track_video;
   MMAL_STATUS_T status = MMAL_EINVAL;
   uint32_t encoding;
   size_t uri_len;

   if(!reader->output_num)
   {
      LOG_ERROR("%s doesn't have output ports", reader->name);
      goto error;
   }

   /* Open the given URI */
   uri_len = strlen(uri);
   param_size = sizeof(MMAL_PARAMETER_STRING_T) + uri_len;
   param = malloc(param_size);
   if(!param)
   {
      LOG_ERROR("out of memory");
      status = MMAL_ENOMEM;
      goto error;
   }
   memset(param, 0, param_size);
   param->hdr.id = MMAL_PARAMETER_URI;
   param->hdr.size = param_size;
   vcos_safe_strcpy(param->str, uri, uri_len + 1, 0);
   status = mmal_port_parameter_set(reader->control, &param->hdr);
   if(status != MMAL_SUCCESS && status != MMAL_ENOSYS)
   {
      LOG_ERROR("%s could not open file %s", reader->name, uri);
      goto error;
   }
   status = MMAL_SUCCESS;

   /* Look for a video track */
   for(track_video = 0; track_video < reader->output_num; track_video++)
      if(reader->output[track_video]->format->type == MMAL_ES_TYPE_VIDEO) break;
   if(track_video != reader->output_num)
   {
      ctx->reader_video = reader->output[track_video];
      /* Try to detect still images */
      encoding = ctx->reader_video->format->encoding;
      if (encoding == MMAL_ENCODING_JPEG ||
          encoding == MMAL_ENCODING_GIF  ||
          encoding == MMAL_ENCODING_PNG  ||
          encoding == MMAL_ENCODING_PPM  ||
          encoding == MMAL_ENCODING_TGA  ||
          encoding == MMAL_ENCODING_BMP)
         ctx->is_still_image = 1;
   }

   /* Look for an audio track */
   for(track_audio = 0; track_audio < reader->output_num; track_audio++)
      if(reader->output[track_audio]->format->type == MMAL_ES_TYPE_AUDIO) break;
   if(track_audio != reader->output_num)
      ctx->reader_audio = reader->output[track_audio];

   if(track_video == reader->output_num &&
      track_audio == reader->output_num)
   {
      LOG_ERROR("no track to decode");
      status = MMAL_EINVAL;
      goto error;
   }

   LOG_INFO("----Reader input port format-----");
   if(track_video != reader->output_num)
      log_format(reader->output[track_video]->format, 0);
   if(track_audio != reader->output_num)
      log_format(reader->output[track_audio]->format, 0);

   if(ctx->options.seeking)
   {
      LOG_DEBUG("seek to %fs", ctx->options.seeking);
      seek.offset = ctx->options.seeking * INT64_C(1000000);
      status = mmal_port_parameter_set(reader->control, &seek.hdr);
      if(status != MMAL_SUCCESS)
         LOG_ERROR("failed to seek to %fs", ctx->options.seeking);
   }

 error:
   if(param)
      free(param);
   return status;
}