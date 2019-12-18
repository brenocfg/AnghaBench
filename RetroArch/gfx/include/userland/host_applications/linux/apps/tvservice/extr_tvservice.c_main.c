#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHI_CONNECTION_T ;
struct TYPE_4__ {char* vendor; char* monitor_name; } ;
typedef  TYPE_1__ TV_DEVICE_ID_T ;
typedef  int /*<<< orphan*/  SDTV_MODE_T ;
typedef  int /*<<< orphan*/  SDTV_ASPECT_T ;
typedef  int /*<<< orphan*/  HDMI_RES_GROUP_T ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_3D_FORMAT_FRAME_PACKING ; 
 int /*<<< orphan*/  HDMI_3D_FORMAT_FRAME_SEQUENTIAL ; 
 int /*<<< orphan*/  HDMI_3D_FORMAT_NONE ; 
 int /*<<< orphan*/  HDMI_3D_FORMAT_SBS_HALF ; 
 int /*<<< orphan*/  HDMI_3D_FORMAT_TB_HALF ; 
 char HDMI_MODE_DVI ; 
 char HDMI_MODE_HDMI ; 
 int /*<<< orphan*/  HDMI_PIXEL_CLOCK_TYPE_NTSC ; 
 int /*<<< orphan*/  HDMI_PIXEL_CLOCK_TYPE_PAL ; 
 int /*<<< orphan*/  HDMI_PROPERTY_3D_STRUCTURE ; 
 int /*<<< orphan*/  HDMI_PROPERTY_PIXEL_CLOCK_TYPE ; 
 int /*<<< orphan*/  HDMI_RES_GROUP_CEA ; 
 int /*<<< orphan*/  HDMI_RES_GROUP_DMT ; 
 int /*<<< orphan*/  HDMI_RES_GROUP_INVALID ; 
 int /*<<< orphan*/  LOG_ERR (char*,...) ; 
 int /*<<< orphan*/  LOG_STD (char*,...) ; 
 char MAX_MODE_ID ; 
 int OPTSTRING_LEN ; 
#define  OPT_AUDIOSUP 141 
#define  OPT_DUMPEDID 140 
#define  OPT_EXPLICIT 139 
#define  OPT_HELP 138 
#define  OPT_JSON 137 
#define  OPT_MODES 136 
#define  OPT_MONITOR 135 
#define  OPT_NAME 134 
#define  OPT_NTSC 133 
#define  OPT_OFF 132 
#define  OPT_PREFERRED 131 
#define  OPT_SDTVON 130 
#define  OPT_SHOWINFO 129 
#define  OPT_STATUS 128 
 int /*<<< orphan*/  SDTV_ASPECT_14_9 ; 
 int /*<<< orphan*/  SDTV_ASPECT_16_9 ; 
 int /*<<< orphan*/  SDTV_ASPECT_4_3 ; 
 int /*<<< orphan*/  SDTV_ASPECT_UNKNOWN ; 
 int /*<<< orphan*/  SDTV_MODE_NTSC ; 
 int /*<<< orphan*/  SDTV_MODE_NTSC_J ; 
 int /*<<< orphan*/  SDTV_MODE_PAL ; 
 int /*<<< orphan*/  SDTV_MODE_PAL_M ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  create_optstring (char*) ; 
 scalar_t__ dump_edid (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ get_audiosup () ; 
 scalar_t__ get_modes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_status () ; 
 int getopt_long_only (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  long_opts ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 int optind ; 
 scalar_t__ power_off () ; 
 scalar_t__ power_on_explicit (int /*<<< orphan*/ ,char,char) ; 
 scalar_t__ power_on_preferred () ; 
 scalar_t__ power_on_sdtv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quit_event ; 
 scalar_t__ set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ show_info (int) ; 
 int /*<<< orphan*/  show_usage () ; 
 int sscanf (char*,char*,char*,char*,char*) ; 
 scalar_t__ start_monitor () ; 
 scalar_t__ vc_tv_get_device_id (TYPE_1__*) ; 
 int /*<<< orphan*/  vc_vchi_tv_init (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  vc_vchi_tv_stop () ; 
 int /*<<< orphan*/  vchi_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_initialise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_event_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_event_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_init () ; 
 int /*<<< orphan*/  vcos_strcasecmp (char*,char*) ; 

int main( int argc, char **argv )
{
   int32_t ret;
   char optstring[OPTSTRING_LEN];
   int  opt;
   int  opt_preferred = 0;
   int  opt_explicit = 0;
   int  opt_ntsc = 0;
   int  opt_sdtvon = 0;
   int  opt_off = 0;
   int  opt_modes = 0;
   int  opt_monitor = 0;
   int  opt_status = 0;
   int  opt_audiosup = 0;
   int  opt_dumpedid = 0;
   int  opt_showinfo = 0;
   int  opt_3d = 0;
   int  opt_json = 0;
   int  opt_name = 0;

   char *dumpedid_filename = NULL;
   VCHI_INSTANCE_T    vchi_instance;
   VCHI_CONNECTION_T *vchi_connection;
   HDMI_RES_GROUP_T power_on_explicit_group = HDMI_RES_GROUP_INVALID;
   uint32_t         power_on_explicit_mode;
   uint32_t         power_on_explicit_drive = HDMI_MODE_HDMI;
   HDMI_RES_GROUP_T get_modes_group = HDMI_RES_GROUP_INVALID;
   SDTV_MODE_T sdtvon_mode = SDTV_MODE_NTSC;
   SDTV_ASPECT_T sdtvon_aspect = SDTV_ASPECT_UNKNOWN;
   int sdtvon_progressive = 0;

   // Initialize VCOS
   vcos_init();

   // Create the option string that we will be using to parse the arguments
   create_optstring( optstring );

   // Parse the command line arguments
   while (( opt = getopt_long_only( argc, argv, optstring, long_opts,
                                    NULL )) != -1 )
   {
      switch ( opt )
      {
         case 0:
         {
            // getopt_long returns 0 for entries where flag is non-NULL
            break;
         }
         case OPT_PREFERRED:
         {
            opt_preferred = 1;
            break;
         }
         case OPT_EXPLICIT:
         {
            char group_str[32], drive_str[32];

            /* coverity[secure_coding] String length specified, so can't overflow */
            int s = sscanf( optarg, "%31s %u %31s", group_str, &power_on_explicit_mode, drive_str );
            if ( s != 2 && s != 3 )
            {
               LOG_ERR( "Invalid arguments '%s'", optarg );
               goto err_out;
            }

            // Check the group first
            if ( vcos_strcasecmp( "CEA", group_str ) == 0 )
            {
               power_on_explicit_group = HDMI_RES_GROUP_CEA;
            }
            else if ( vcos_strcasecmp( "DMT", group_str ) == 0 )
            {
               power_on_explicit_group = HDMI_RES_GROUP_DMT;
            }
            else if ( vcos_strcasecmp( "CEA_3D", group_str ) == 0  ||
                      vcos_strcasecmp( "CEA_3D_SBS", group_str ) == 0)
            {
               power_on_explicit_group = HDMI_RES_GROUP_CEA;
               opt_3d = 1;
            }
            else if ( vcos_strcasecmp( "CEA_3D_TB", group_str ) == 0 )
            {
               power_on_explicit_group = HDMI_RES_GROUP_CEA;
               opt_3d = 2;
            }
            else if ( vcos_strcasecmp( "CEA_3D_FP", group_str ) == 0 )
            {
               power_on_explicit_group = HDMI_RES_GROUP_CEA;
               opt_3d = 3;
            }
            else if ( vcos_strcasecmp( "CEA_3D_FS", group_str ) == 0 )
            {
               power_on_explicit_group = HDMI_RES_GROUP_CEA;
               opt_3d = 4;
            }
            else
            {
               LOG_ERR( "Invalid group '%s'", group_str );
               goto err_out;
            }
            if (s==3)
            {
               if (vcos_strcasecmp( "HDMI", drive_str ) == 0 )
               {
                  power_on_explicit_drive = HDMI_MODE_HDMI;
               }
               else if (vcos_strcasecmp( "DVI", drive_str ) == 0 )
               {
                  power_on_explicit_drive = HDMI_MODE_DVI;
               }
               else
               {
                  LOG_ERR( "Invalid drive '%s'", drive_str );
                  goto err_out;
               }
            }
            // Then check if mode is a sane number
            if ( power_on_explicit_mode > MAX_MODE_ID )
            {
               LOG_ERR( "Invalid mode '%u'", power_on_explicit_mode );
               goto err_out;
            }

            opt_explicit = 1;
            break;
         }
         case OPT_NTSC:
         {
            opt_ntsc = 1;
            break;
         }
         case OPT_SDTVON:
         {
            char mode_str[32], aspect_str[32], progressive_str[32];
            int s = sscanf( optarg, "%s %s %s", mode_str, aspect_str, progressive_str );
            if ( s != 2 && s != 3 )
            {
               LOG_ERR( "Invalid arguments '%s'", optarg );
               goto err_out;
            }

            // Check the group first
            if ( vcos_strcasecmp( "NTSC", mode_str ) == 0 )
            {
               sdtvon_mode = SDTV_MODE_NTSC;
            }
            else if ( vcos_strcasecmp( "NTSC_J", mode_str ) == 0 )
            {
               sdtvon_mode = SDTV_MODE_NTSC_J;
            }
            else if ( vcos_strcasecmp( "PAL", mode_str ) == 0 )
            {
               sdtvon_mode = SDTV_MODE_PAL;
            }
            else if ( vcos_strcasecmp( "PAL_M", mode_str ) == 0 )
            {
               sdtvon_mode = SDTV_MODE_PAL_M;
            }
            else
            {
               LOG_ERR( "Invalid mode '%s'", mode_str );
               goto err_out;
            }

            if ( vcos_strcasecmp( "4:3", aspect_str ) == 0 )
            {
               sdtvon_aspect = SDTV_ASPECT_4_3;
            }
            else if ( vcos_strcasecmp( "14:9", aspect_str ) == 0 )
            {
               sdtvon_aspect = SDTV_ASPECT_14_9;
            }
            else if ( vcos_strcasecmp( "16:9", aspect_str ) == 0 )
            {
               sdtvon_aspect = SDTV_ASPECT_16_9;
            }

            if (s == 3 && vcos_strcasecmp( "P", progressive_str ) == 0 )
            {
              sdtvon_progressive = 1;
            }
            opt_sdtvon = 1;
            break;
         }
         case OPT_OFF:
         {
            opt_off = 1;
            break;
         }
         case OPT_MODES:
         {
            if ( vcos_strcasecmp( "CEA", optarg ) == 0 )
            {
               get_modes_group = HDMI_RES_GROUP_CEA;
            }
            else if ( vcos_strcasecmp( "DMT", optarg ) == 0 )
            {
               get_modes_group = HDMI_RES_GROUP_DMT;
            }
            else
            {
               LOG_ERR( "Invalid group '%s'", optarg );
               goto err_out;
            }

            opt_modes = 1;
            break;
         }
         case OPT_MONITOR:
         {
            opt_monitor = 1;
            break;
         }
         case OPT_STATUS:
         {
            opt_status = 1;
            break;
         }
         case OPT_AUDIOSUP:
         {
            opt_audiosup = 1;
            break;
         }
         case OPT_DUMPEDID:
         {
            opt_dumpedid = 1;
            dumpedid_filename = optarg;
            break;
         }
         case OPT_SHOWINFO:
         {
            opt_showinfo = atoi(optarg)+1;
            break;
         }
         case OPT_JSON:
         {
            opt_json = 1;
            break;
         }
         case OPT_NAME:
         {
            opt_name = 1;
            break;
         }
         default:
         {
            LOG_ERR( "Unrecognized option '%d'\n", opt );
            goto err_usage;
         }
         case '?':
         case OPT_HELP:
         {
            goto err_usage;
         }
      } // end switch
   } // end while

   argc -= optind;
   argv += optind;

   if (( optind == 1 ) || ( argc > 0 ))
   {
      if ( argc > 0 )
      {
         LOG_ERR( "Unrecognized argument -- '%s'", *argv );
      }

      goto err_usage;
   }

   if (( opt_preferred + opt_explicit + opt_sdtvon > 1 ))
   {
      LOG_ERR( "Conflicting power on options" );
      goto err_usage;
   }

   if ((( opt_preferred == 1 ) || ( opt_explicit == 1 ) || ( opt_sdtvon == 1)) && ( opt_off == 1 ))
   {
      LOG_ERR( "Cannot power on and power off simultaneously" );
      goto err_out;
   }

   // Initialize the VCHI connection
   ret = vchi_initialise( &vchi_instance );
   if ( ret != 0 )
   {
      LOG_ERR( "Failed to initialize VCHI (ret=%d)", ret );
      goto err_out;
   }

   ret = vchi_connect( NULL, 0, vchi_instance );
   if ( ret != 0)
   {
      LOG_ERR( "Failed to create VCHI connection (ret=%d)", ret );
      goto err_out;
   }

//   LOG_INFO( "Starting tvservice" );

   // Initialize the tvservice
   vc_vchi_tv_init( vchi_instance, &vchi_connection, 1 );

   if ( opt_monitor == 1 )
   {
      LOG_STD( "Starting to monitor for HDMI events" );

      if ( start_monitor() != 0 )
      {
         goto err_stop_service;
      }
   }

   if ( opt_modes == 1 )
   {
      if ( get_modes( get_modes_group, opt_json ) != 0 )
      {
         goto err_stop_service;
      }
   }

   if ( opt_preferred == 1 )
   {
      if(set_property( HDMI_PROPERTY_3D_STRUCTURE, HDMI_3D_FORMAT_NONE, 0) != 0)
      {
         goto err_stop_service;
      }
      if ( power_on_preferred() != 0 )
      {
         goto err_stop_service;
      }
   }
   else if ( opt_explicit == 1 )
   {
      //Distinguish between turning on 3D side by side and 3D top/bottom
      if(opt_3d == 0 && set_property( HDMI_PROPERTY_3D_STRUCTURE, HDMI_3D_FORMAT_NONE, 0) != 0)
      {
         goto err_stop_service;
      }
      else if(opt_3d == 1 && set_property( HDMI_PROPERTY_3D_STRUCTURE, HDMI_3D_FORMAT_SBS_HALF, 0) != 0)
      {
         goto err_stop_service;
      }
      else if(opt_3d == 2 && set_property( HDMI_PROPERTY_3D_STRUCTURE, HDMI_3D_FORMAT_TB_HALF, 0) != 0)
      {
         goto err_stop_service;
      }
      else if(opt_3d == 3 && set_property( HDMI_PROPERTY_3D_STRUCTURE, HDMI_3D_FORMAT_FRAME_PACKING, 0) != 0)
      {
         goto err_stop_service;
      }
      else if(opt_3d == 4 && set_property( HDMI_PROPERTY_3D_STRUCTURE, HDMI_3D_FORMAT_FRAME_SEQUENTIAL, 0) != 0)
      {
         goto err_stop_service;
      }
      if (set_property( HDMI_PROPERTY_PIXEL_CLOCK_TYPE, opt_ntsc ? HDMI_PIXEL_CLOCK_TYPE_NTSC : HDMI_PIXEL_CLOCK_TYPE_PAL, 0) != 0)
      {
         goto err_stop_service;
      }
      if ( power_on_explicit( power_on_explicit_group,
                              power_on_explicit_mode, power_on_explicit_drive ) != 0 )
      {
         goto err_stop_service;
      }
   }
   else if ( opt_sdtvon == 1 )
   {
      if ( power_on_sdtv( sdtvon_mode,
                              sdtvon_aspect, sdtvon_progressive ) != 0 )
      {
         goto err_stop_service;
      }
   }
   else if (opt_off == 1 )
   {
      if ( power_off() != 0 )
      {
         goto err_stop_service;
      }
   }

   if ( opt_status == 1 )
   {
      if ( get_status() != 0 )
      {
         goto err_stop_service;
      }
   }

   if ( opt_audiosup == 1 )
   {
      if ( get_audiosup() != 0 )
      {
         goto err_stop_service;
      }
   }

   if ( opt_dumpedid == 1 )
   {
      if ( dump_edid(dumpedid_filename) != 0 )
      {
         goto err_stop_service;
      }
   }

   if ( opt_showinfo )
   {
      if ( show_info(opt_showinfo-1) != 0 )
      {
         goto err_stop_service;
      }
   }

   if ( opt_name == 1 )
   {
      TV_DEVICE_ID_T id;
      memset(&id, 0, sizeof(id));
      if(vc_tv_get_device_id(&id) == 0) {
         if(id.vendor[0] == '\0' || id.monitor_name[0] == '\0') {
            LOG_ERR( "No device present" );
         } else {
            LOG_STD( "device_name=%s-%s", id.vendor, id.monitor_name);
         }
      } else {
         LOG_ERR( "Failed to obtain device name" );
      }
   }

   if ( opt_monitor == 1 )
   {
      // Wait until we get the signal to exit
      vcos_event_wait( &quit_event );

      vcos_event_delete( &quit_event );
   }

err_stop_service:
//   LOG_INFO( "Stopping tvservice" );

   // Stop the tvservice
   vc_vchi_tv_stop();

   // Disconnect the VCHI connection
   vchi_disconnect( vchi_instance );

   exit( 0 );

err_usage:
   show_usage();

err_out:
   exit( 1 );
}