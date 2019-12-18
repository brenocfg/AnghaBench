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
struct TYPE_13__ {TYPE_3__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_14__ {char* value; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {TYPE_1__* io; TYPE_2__* module; } ;
struct TYPE_11__ {int /*<<< orphan*/ * header_list; } ;
struct TYPE_10__ {char* uri; } ;
typedef  TYPE_5__ RTSP_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT_BASE_NAME ; 
 int /*<<< orphan*/  CONTENT_LOCATION_NAME ; 
 int /*<<< orphan*/  CONTENT_PSEUDOHEADER_NAME ; 
 int /*<<< orphan*/  LOG_ERROR (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  rtsp_create_tracks_from_sdp (TYPE_4__*,char*,char*) ; 
 scalar_t__ vc_containers_list_find_entry (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_create_tracks_from_response( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINERS_LIST_T *header_list = p_ctx->priv->module->header_list;
   RTSP_HEADER_T header;
   char *base_uri;
   char *content;

   header.name = CONTENT_PSEUDOHEADER_NAME;
   if (!vc_containers_list_find_entry(header_list, &header))
   {
      LOG_ERROR(p_ctx, "RTSP: Content missing");
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }
   content = header.value;

   /* The control URI may be relative to a base URI which is the first of these
    * that is available:
    *    1. Content-Base header
    *    2. Content-Location header
    *    3. Request URI
    */
   header.name = CONTENT_BASE_NAME;
   if (vc_containers_list_find_entry(header_list, &header))
      base_uri = header.value;
   else {
      header.name = CONTENT_LOCATION_NAME;
      if (vc_containers_list_find_entry(header_list, &header))
         base_uri = header.value;
      else
         base_uri = p_ctx->priv->io->uri;
   }

   return rtsp_create_tracks_from_sdp(p_ctx, content, base_uri);
}