#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_13__ {int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {char* name; char* value; int /*<<< orphan*/  mode; } ;
struct TYPE_10__ {TYPE_1__* module; } ;
struct TYPE_9__ {scalar_t__ extra; } ;
typedef  TYPE_4__ PARAMETER_T ;
typedef  TYPE_5__ MP4_PAYLOAD_T ;
typedef  TYPE_4__ MP4_MODE_ENTRY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  const mp4_mode_lookup ; 
 int /*<<< orphan*/  vc_containers_list_find_entry (int /*<<< orphan*/  const*,TYPE_4__*) ; 
 int /*<<< orphan*/  vc_containers_list_validate (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_get_mode(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      const VC_CONTAINERS_LIST_T *params)
{
   MP4_PAYLOAD_T *extra = (MP4_PAYLOAD_T *)track->priv->module->extra;
   PARAMETER_T param;
   MP4_MODE_ENTRY_T mode_entry;

   param.name = "mode";
   if (!vc_containers_list_find_entry(params, &param) || !param.value)
   {
      LOG_ERROR(p_ctx, "MPEG-4: mode parameter missing");
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

#ifdef RTP_DEBUG
   vc_containers_list_validate(&mp4_mode_lookup);
#endif

   mode_entry.name = param.value;
   if (!vc_containers_list_find_entry(&mp4_mode_lookup, &mode_entry))
   {
      LOG_ERROR(p_ctx, "MPEG-4: Unrecognised mode parameter \"%s\"", mode_entry.name);
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

   extra->mode = mode_entry.mode;

   return VC_CONTAINER_SUCCESS;
}