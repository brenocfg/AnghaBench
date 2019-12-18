#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_8__ {void* aspect; } ;
struct TYPE_11__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/  is_valid; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/  is_valid; } ;
struct TYPE_13__ {int notify_length; int copy_protect; int hdmi_preferred_mode; int hdmi_current_mode; int sdtv_current_colour; scalar_t__ to_exit; TYPE_2__* callbacks; int /*<<< orphan*/  sdtv_current_cp_mode; TYPE_1__ sdtv_options; void* sdtv_current_mode; void* hdmi_current_group; int /*<<< orphan*/ * notify_handle; void* hdmi_preferred_group; TYPE_4__ dmt_cache; TYPE_3__ cea_cache; int /*<<< orphan*/ * notify_buffer; int /*<<< orphan*/  initialised; } ;
struct TYPE_12__ {int state; } ;
struct TYPE_9__ {int /*<<< orphan*/  notify_data; int /*<<< orphan*/  (* notify_fn ) (int /*<<< orphan*/ ,int,int,int) ;} ;
typedef  TYPE_5__ TV_DISPLAY_STATE_T ;
typedef  TYPE_6__ TVSERVICE_HOST_STATE_T ;
typedef  void* SDTV_MODE_T ;
typedef  int /*<<< orphan*/  SDTV_CP_MODE_T ;
typedef  void* SDTV_ASPECT_T ;
typedef  void* HDMI_RES_GROUP_T ;

/* Variables and functions */
 int SDTV_COLOUR_RGB ; 
 void* SDTV_COLOUR_UNKNOWN ; 
 int SDTV_COLOUR_YPRPB ; 
 int /*<<< orphan*/  SDTV_CP_NONE ; 
 void* SDTV_MODE_OFF ; 
 int TVSERVICE_MAX_CALLBACKS ; 
 int /*<<< orphan*/  VCHI_FLAGS_NONE ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
#define  VC_HDMI_ATTACHED 141 
#define  VC_HDMI_DVI 140 
#define  VC_HDMI_HDCP_AUTH 139 
#define  VC_HDMI_HDCP_KEY_DOWNLOAD 138 
#define  VC_HDMI_HDCP_SRM_DOWNLOAD 137 
#define  VC_HDMI_HDCP_UNAUTH 136 
#define  VC_HDMI_HDMI 135 
#define  VC_HDMI_UNPLUGGED 134 
#define  VC_SDTV_ATTACHED 133 
#define  VC_SDTV_CP_ACTIVE 132 
#define  VC_SDTV_CP_INACTIVE 131 
#define  VC_SDTV_NTSC 130 
#define  VC_SDTV_PAL 129 
#define  VC_SDTV_UNPLUGGED 128 
 int /*<<< orphan*/  VC_TV_GET_DISPLAY_STATE ; 
 int VC_VTOH32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ tvservice_lock_obtain () ; 
 int /*<<< orphan*/  tvservice_lock_release () ; 
 int /*<<< orphan*/  tvservice_notify_available_event ; 
 scalar_t__ tvservice_send_command_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  vc_tv_notification_name (int) ; 
 scalar_t__ vchi_msg_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_service_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_event_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,...) ; 

__attribute__((used)) static void *tvservice_notify_func(void *arg) {
   int32_t success;
   TVSERVICE_HOST_STATE_T *state = (TVSERVICE_HOST_STATE_T *) arg;
   TV_DISPLAY_STATE_T tvstate;

   vcos_log_trace("TV service async thread started");
   /* Check starting state, and put service in use if necessary */
   success = tvservice_send_command_reply( VC_TV_GET_DISPLAY_STATE, NULL, 0, &tvstate, sizeof(TV_DISPLAY_STATE_T));
   if (success != 0)
      return 0;
   if (tvstate.state & VC_HDMI_ATTACHED)
   {
      /* Connected */
      if (tvstate.state & (VC_HDMI_HDMI | VC_HDMI_DVI))
      {
         /* Mode already selected */
         vchi_service_use(state->notify_handle[0]);
      }
   }
   // the state machine below only wants a single bit to be set
   if (tvstate.state & (VC_HDMI_ATTACHED|VC_HDMI_UNPLUGGED))
      tvstate.state &= ~(VC_HDMI_HDMI | VC_HDMI_DVI);

   while(1) {
      VCOS_STATUS_T status = vcos_event_wait(&tvservice_notify_available_event);
      if(status != VCOS_SUCCESS || !state->initialised || state->to_exit)
         break;

      do {
         uint32_t reason, param1, param2;
         //Get all notifications in the queue
         success = vchi_msg_dequeue( state->notify_handle[0], state->notify_buffer, sizeof(state->notify_buffer), &state->notify_length, VCHI_FLAGS_NONE );
         if(success != 0 || state->notify_length < sizeof(uint32_t)*3 ) {
            vcos_assert(state->notify_length == sizeof(uint32_t)*3);
            break;
         }

         if(tvservice_lock_obtain() != 0)
            break;

         //Check what notification it is and update ourselves accordingly before notifying the host app
         //All notifications are of format: reason, param1, param2 (all 32-bit unsigned int)
         reason = VC_VTOH32(state->notify_buffer[0]), param1 = VC_VTOH32(state->notify_buffer[1]), param2 = VC_VTOH32(state->notify_buffer[2]);
         vcos_log_trace("[%s] %s %d %d", VCOS_FUNCTION, vc_tv_notification_name(reason),
                        param1, param2);
         switch(reason) {
         case VC_HDMI_UNPLUGGED:
            if(tvstate.state & (VC_HDMI_HDMI|VC_HDMI_DVI)) {
               state->copy_protect = 0;
               if((tvstate.state & VC_HDMI_ATTACHED) == 0) {
                  vchi_service_release(state->notify_handle[0]);
               }
            }
            tvstate.state &= ~(VC_HDMI_HDMI|VC_HDMI_DVI|VC_HDMI_ATTACHED|VC_HDMI_HDCP_AUTH);
            tvstate.state |= (VC_HDMI_UNPLUGGED | VC_HDMI_HDCP_UNAUTH);
            vcos_log_trace("[%s] invalidating caches", VCOS_FUNCTION);
            state->cea_cache.is_valid = state->cea_cache.num_modes = 0;
            state->dmt_cache.is_valid = state->dmt_cache.num_modes = 0;
            break;

         case VC_HDMI_ATTACHED:
            if(tvstate.state & (VC_HDMI_HDMI|VC_HDMI_DVI)) {
               state->copy_protect = 0;
               vchi_service_release(state->notify_handle[0]);
            }
            tvstate.state &=  ~(VC_HDMI_HDMI|VC_HDMI_DVI|VC_HDMI_UNPLUGGED|VC_HDMI_HDCP_AUTH);
            tvstate.state |= VC_HDMI_ATTACHED;
            state->hdmi_preferred_group = (HDMI_RES_GROUP_T) param1;
            state->hdmi_preferred_mode = param2;
            break;

         case VC_HDMI_DVI:
            if(tvstate.state & (VC_HDMI_ATTACHED|VC_HDMI_UNPLUGGED)) {
               vchi_service_use(state->notify_handle[0]);
            }
            tvstate.state &= ~(VC_HDMI_HDMI|VC_HDMI_ATTACHED|VC_HDMI_UNPLUGGED);
            tvstate.state |= VC_HDMI_DVI;
            state->hdmi_current_group = (HDMI_RES_GROUP_T) param1;
            state->hdmi_current_mode = param2;
            break;

         case VC_HDMI_HDMI:
            if(tvstate.state & (VC_HDMI_ATTACHED|VC_HDMI_UNPLUGGED)) {
               vchi_service_use(state->notify_handle[0]);
            }
            tvstate.state &= ~(VC_HDMI_DVI|VC_HDMI_ATTACHED|VC_HDMI_UNPLUGGED);
            tvstate.state |= VC_HDMI_HDMI;
            state->hdmi_current_group = (HDMI_RES_GROUP_T) param1;
            state->hdmi_current_mode = param2;
            break;

         case VC_HDMI_HDCP_UNAUTH:
            tvstate.state &= ~VC_HDMI_HDCP_AUTH;
            tvstate.state |= VC_HDMI_HDCP_UNAUTH;
            state->copy_protect = 0;
            //Do we care about the reason for HDCP unauth in param1?
            break;

         case VC_HDMI_HDCP_AUTH:
            tvstate.state &= ~VC_HDMI_HDCP_UNAUTH;
            tvstate.state |= VC_HDMI_HDCP_AUTH;
            state->copy_protect = 1;
            break;

         case VC_HDMI_HDCP_KEY_DOWNLOAD:
         case VC_HDMI_HDCP_SRM_DOWNLOAD:
            //Nothing to do here, just tell the host app whether it is successful or not (in param1)
            break;

         case VC_SDTV_UNPLUGGED: //Currently we don't get this
            if(tvstate.state & (VC_SDTV_PAL | VC_SDTV_NTSC)) {
               state->copy_protect = 0;
            }
            tvstate.state &= ~(VC_SDTV_ATTACHED | VC_SDTV_PAL | VC_SDTV_NTSC);
            tvstate.state |= (VC_SDTV_UNPLUGGED | VC_SDTV_CP_INACTIVE);
            state->sdtv_current_mode = SDTV_MODE_OFF;
            break;

         case VC_SDTV_ATTACHED: //Currently we don't get this either
            tvstate.state &= ~(VC_SDTV_UNPLUGGED | VC_SDTV_PAL | VC_SDTV_NTSC);
            tvstate.state |= VC_SDTV_ATTACHED;
            state->sdtv_current_mode = SDTV_MODE_OFF;
            break;

         case VC_SDTV_NTSC:
            tvstate.state &= ~(VC_SDTV_UNPLUGGED | VC_SDTV_ATTACHED | VC_SDTV_PAL);
            tvstate.state |= VC_SDTV_NTSC;
            state->sdtv_current_mode = (SDTV_MODE_T) param1;
            state->sdtv_options.aspect = (SDTV_ASPECT_T) param2;
            if(param1 & SDTV_COLOUR_RGB) {
               state->sdtv_current_colour = SDTV_COLOUR_RGB;
            } else if(param1 & SDTV_COLOUR_YPRPB) {
               state->sdtv_current_colour = SDTV_COLOUR_YPRPB;
            } else {
               state->sdtv_current_colour = SDTV_COLOUR_UNKNOWN;
            }
            break;

         case VC_SDTV_PAL:
            tvstate.state &= ~(VC_SDTV_UNPLUGGED | VC_SDTV_ATTACHED | VC_SDTV_NTSC);
            tvstate.state |= VC_SDTV_PAL;
            state->sdtv_current_mode = (SDTV_MODE_T) param1;
            state->sdtv_options.aspect = (SDTV_ASPECT_T) param2;
            if(param1 & SDTV_COLOUR_RGB) {
               state->sdtv_current_colour = SDTV_COLOUR_RGB;
            } else if(param1 & SDTV_COLOUR_YPRPB) {
               state->sdtv_current_colour = SDTV_COLOUR_YPRPB;
            } else {
               state->sdtv_current_colour = SDTV_COLOUR_UNKNOWN;
            }
            break;

         case VC_SDTV_CP_INACTIVE:
            tvstate.state &= ~VC_SDTV_CP_ACTIVE;
            tvstate.state |= VC_SDTV_CP_INACTIVE;
            state->copy_protect = 0;
            state->sdtv_current_cp_mode = SDTV_CP_NONE;
            break;

         case VC_SDTV_CP_ACTIVE:
            tvstate.state &= ~VC_SDTV_CP_INACTIVE;
            tvstate.state |= VC_SDTV_CP_ACTIVE;
            state->copy_protect = 1;
            state->sdtv_current_cp_mode = (SDTV_CP_MODE_T) param1;
            break;
         }

         tvservice_lock_release();

         //Now callback the host app(s)
         uint32_t i, called = 0;
         for(i = 0; i < TVSERVICE_MAX_CALLBACKS; i++)
         {
            if(state->callbacks[i].notify_fn != NULL)
            {
               called++;
               state->callbacks[i].notify_fn
                  (state->callbacks[i].notify_data, reason, param1, param2);
            } // if
         } // for
         if(called == 0) {
            vcos_log_info("TV service: No callback handler specified, callback [%s] swallowed",
                          vc_tv_notification_name(reason));
         }
      } while(success == 0 && state->notify_length >= sizeof(uint32_t)*3); //read the next message if any
   } //while (1)

   if(state->to_exit)
      vcos_log_trace("TV service async thread exiting");

   return 0;
}