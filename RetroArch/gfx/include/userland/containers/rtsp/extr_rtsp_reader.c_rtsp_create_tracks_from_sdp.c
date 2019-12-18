#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_2__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
struct TYPE_22__ {TYPE_4__* priv; int /*<<< orphan*/  tracks_num; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_20__ {TYPE_3__* module; } ;
struct TYPE_19__ {int /*<<< orphan*/  media_item; } ;
struct TYPE_18__ {TYPE_1__* module; } ;
struct TYPE_17__ {char* control_uri; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  attribute_name_delimiter_fn ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ rtsp_complete_track (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ rtsp_create_track_for_media_field (TYPE_6__*,char*,TYPE_5__**) ; 
 scalar_t__ rtsp_parse_control_attribute (TYPE_6__*,char*,char*,char**) ; 
 char* rtsp_parse_extract (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rtsp_parse_fmtp_attribute (TYPE_6__*,TYPE_5__*,char*) ; 
 scalar_t__ rtsp_parse_rtpmap_attribute (TYPE_6__*,TYPE_5__*,char*) ; 
 char* rtsp_trim (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_create_tracks_from_sdp( VC_CONTAINER_T *p_ctx,
      char *sdp_buffer,
      char *base_uri )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_TRACK_T *track = NULL;
   char *session_base_uri = base_uri;
   char *ptr;
   char *next_line_ptr;
   char *attribute;

   for (ptr = sdp_buffer; status == VC_CONTAINER_SUCCESS && *ptr; ptr = next_line_ptr)
   {
      /* Find end of line */
      char field = *ptr;

      next_line_ptr = ptr;
      while (*next_line_ptr && *next_line_ptr != '\n')
         next_line_ptr++;

      /* Terminate line */
      if (*next_line_ptr)
         *next_line_ptr++ = '\0';

      /* The format of the line has to be "<field>=<value>" where <field> is a single
       * character. Ignore anything else. */
      if (ptr[1] != '=')
         continue;
      ptr = rtsp_trim(ptr + 2);

      switch (field)
      {
      case 'm':
         /* Start of media item */
         if (track)
         {
            /* Finish previous track */
            status = rtsp_complete_track(p_ctx, track);
            track = NULL;
            p_ctx->priv->module->media_item++;
            if (status != VC_CONTAINER_SUCCESS)
               break;
         }

         status = rtsp_create_track_for_media_field(p_ctx, ptr, &track);
         break;
      case 'a':   /* Attribute (either session or media level) */
         /* Attributes of the form "a=<name>:<value>" */
         attribute = rtsp_parse_extract(&ptr, attribute_name_delimiter_fn, NULL);

         if (track)
         {
            /* Media level attribute */

            /* Look for known attributes */
            if (strcmp(attribute, "rtpmap") == 0)
               status = rtsp_parse_rtpmap_attribute(p_ctx, track, ptr);
            else if (strcmp(attribute, "fmtp") == 0)
               status = rtsp_parse_fmtp_attribute(p_ctx, track, ptr);
            else if (strcmp(attribute, "control") == 0)
            {
               char **track_control_uri = &track->priv->module->control_uri;

               if (*track_control_uri)
               {
                  free(*track_control_uri);
                  *track_control_uri = NULL;
               }
               status = rtsp_parse_control_attribute(p_ctx, ptr, session_base_uri, track_control_uri);
            }
            /* Any other attributes are ignored */
         } else {
            /* Session level attribute */
            if (strcmp(attribute, "control") == 0)
            {
               /* Only need to change the session_base_uri if it differs from the base URI */
               ptr = rtsp_trim(ptr);
               if (session_base_uri != base_uri)
               {
                  free(session_base_uri);
                  session_base_uri = base_uri;
               }
               if (strcmp(ptr, base_uri) != 0)
                  status = rtsp_parse_control_attribute(p_ctx, ptr, base_uri, &session_base_uri);
            }
         }
         break;
      default:    /* Ignore any other field names */
         ;
      }
   }

   if (session_base_uri && session_base_uri != base_uri)
      free(session_base_uri);

   /* Having no media fields is an error, since there will be nothing to play back */
   if (status == VC_CONTAINER_SUCCESS)
   {
      if (!p_ctx->tracks_num)
         status = VC_CONTAINER_ERROR_FORMAT_INVALID;
      else if (track)
      {
         /* Finish final track */
         status = rtsp_complete_track(p_ctx, track);
         p_ctx->priv->module->media_item++;
      }
   }

   return status;
}