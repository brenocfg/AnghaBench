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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO (char*,...) ; 
#define  VC_HDMI_ATTACHED 135 
#define  VC_HDMI_DVI 134 
#define  VC_HDMI_HDCP_AUTH 133 
#define  VC_HDMI_HDCP_KEY_DOWNLOAD 132 
#define  VC_HDMI_HDCP_SRM_DOWNLOAD 131 
#define  VC_HDMI_HDCP_UNAUTH 130 
#define  VC_HDMI_HDMI 129 
#define  VC_HDMI_UNPLUGGED 128 

__attribute__((used)) static void tvservice_callback( void *callback_data,
                                uint32_t reason,
                                uint32_t param1,
                                uint32_t param2 )
{
   (void)callback_data;
   (void)param1;
   (void)param2;

   switch ( reason )
   {
      case VC_HDMI_UNPLUGGED:
      {
         LOG_INFO( "HDMI cable is unplugged" );
         break;
      }
      case VC_HDMI_ATTACHED:
      {
         LOG_INFO( "HDMI is attached" );
         break;
      }
      case VC_HDMI_DVI:
      {
         LOG_INFO( "HDMI in DVI mode" );
         break;
      }
      case VC_HDMI_HDMI:
      {
         LOG_INFO( "HDMI in HDMI mode" );
         break;
      }
      case VC_HDMI_HDCP_UNAUTH:
      {
         LOG_INFO( "HDCP authentication is broken" );
         break;
      }
      case VC_HDMI_HDCP_AUTH:
      {
         LOG_INFO( "HDCP is active" );
         break;
      }
      case VC_HDMI_HDCP_KEY_DOWNLOAD:
      {
         LOG_INFO( "HDCP key download" );
         break;
      }
      case VC_HDMI_HDCP_SRM_DOWNLOAD:
      {
         LOG_INFO( "HDCP revocation list download" );
         break;
      }
      default:
      {
         // Ignore all other reasons
         LOG_INFO( "Callback with reason %d", reason );
         break;
      }
   }
}