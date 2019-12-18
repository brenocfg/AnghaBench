#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char const* format; int /*<<< orphan*/  encoding; } ;
struct TYPE_15__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {int /*<<< orphan*/  opacity; TYPE_2__ previewWindow; } ;
struct TYPE_13__ {int /*<<< orphan*/  verbose; int /*<<< orphan*/  opacity; int /*<<< orphan*/  preview_height; int /*<<< orphan*/  preview_width; int /*<<< orphan*/  preview_y; int /*<<< orphan*/  preview_x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  gl_win_defined; } ;
struct TYPE_10__ {int /*<<< orphan*/  quality; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  enable; } ;
struct TYPE_12__ {int quality; int wantRAW; int frameStart; int datetime; int timestamp; int timeout; int demoInterval; int demoMode; int timelapse; int fullResPreview; int useGL; int glCapture; int burstCaptureMode; int restart_interval; TYPE_7__ common_settings; TYPE_5__ raspitex_state; TYPE_6__ preview_parameters; int /*<<< orphan*/  camera_parameters; int /*<<< orphan*/  frameNextMethod; int /*<<< orphan*/  enableExifTags; int /*<<< orphan*/  encoding; TYPE_1__ thumbnailConfig; int /*<<< orphan*/  linkname; } ;
typedef  TYPE_3__ RASPISTILL_STATE ;

/* Variables and functions */
#define  CommandBurstMode 146 
#define  CommandDateTime 145 
#define  CommandDemoMode 144 
#define  CommandEncoding 143 
#define  CommandExifTag 142 
#define  CommandFrameStart 141 
#define  CommandFullResPreview 140 
#define  CommandGL 139 
#define  CommandGLCapture 138 
#define  CommandKeypress 137 
#define  CommandLink 136 
#define  CommandQuality 135 
#define  CommandRaw 134 
#define  CommandRestartInterval 133 
#define  CommandSignal 132 
#define  CommandThumbnail 131 
#define  CommandTimeStamp 130 
#define  CommandTimelapse 129 
#define  CommandTimeout 128 
 int /*<<< orphan*/  FRAME_NEXT_FOREVER ; 
 int /*<<< orphan*/  FRAME_NEXT_IMMEDIATELY ; 
 int /*<<< orphan*/  FRAME_NEXT_KEYPRESS ; 
 int /*<<< orphan*/  FRAME_NEXT_SIGNAL ; 
 int /*<<< orphan*/  FRAME_NEXT_SINGLE ; 
 int /*<<< orphan*/  FRAME_NEXT_TIMELAPSE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  application_help_message ; 
 int /*<<< orphan*/  cmdline_commands ; 
 int /*<<< orphan*/  cmdline_commands_size ; 
 int /*<<< orphan*/  default_signal_handler ; 
 TYPE_9__* encoding_xref ; 
 int encoding_xref_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int raspicamcontrol_parse_cmdline (int /*<<< orphan*/ *,char const*,char const*) ; 
 int raspicli_get_command_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int*) ; 
 int raspicommonsettings_parse_cmdline (TYPE_7__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int raspipreview_parse_cmdline (TYPE_6__*,char const*,char const*) ; 
 int raspitex_parse_cmdline (TYPE_5__*,char const*,char const*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  store_exif_tag (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_cmdline(int argc, const char **argv, RASPISTILL_STATE *state)
{
   // Parse the command line arguments.
   // We are looking for --<something> or -<abbreviation of something>

   int valid = 1;
   int i;

   for (i = 1; i < argc && valid; i++)
   {
      int command_id, num_parameters;

      if (!argv[i])
         continue;

      if (argv[i][0] != '-')
      {
         valid = 0;
         continue;
      }

      // Assume parameter is valid until proven otherwise
      valid = 1;

      command_id = raspicli_get_command_id(cmdline_commands, cmdline_commands_size, &argv[i][1], &num_parameters);

      // If we found a command but are missing a parameter, continue (and we will drop out of the loop)
      if (command_id != -1 && num_parameters > 0 && (i + 1 >= argc) )
         continue;

      //  We are now dealing with a command line option
      switch (command_id)
      {
      case CommandQuality: // Quality = 1-100
         if (sscanf(argv[i + 1], "%u", &state->quality) == 1)
         {
            if (state->quality > 100)
            {
               fprintf(stderr, "Setting max quality = 100\n");
               state->quality = 100;
            }
            i++;
         }
         else
            valid = 0;
         break;

      case CommandRaw: // Add raw bayer data in metadata
         state->wantRAW = 1;
         break;

      case CommandLink :
      {
         int len = strlen(argv[i+1]);
         if (len)
         {
            state->linkname = malloc(len + 10);
            vcos_assert(state->linkname);
            if (state->linkname)
               strncpy(state->linkname, argv[i + 1], len+1);
            i++;
         }
         else
            valid = 0;
         break;

      }

      case CommandFrameStart:  // use a staring value != 0
      {
         if (sscanf(argv[i + 1], "%d", &state->frameStart) == 1)
         {
            i++;
         }
         else
            valid = 0;
         break;
      }

      case CommandDateTime: // use datetime
         state->datetime = 1;
         break;

      case CommandTimeStamp: // use timestamp
         state->timestamp = 1;
         break;

      case CommandTimeout: // Time to run viewfinder for before taking picture, in seconds
      {
         if (sscanf(argv[i + 1], "%d", &state->timeout) == 1)
         {
            // Ensure that if previously selected CommandKeypress we don't overwrite it
            if (state->timeout == 0 && state->frameNextMethod == FRAME_NEXT_SINGLE)
               state->frameNextMethod = FRAME_NEXT_FOREVER;

            i++;
         }
         else
            valid = 0;
         break;
      }

      case CommandThumbnail : // thumbnail parameters - needs string "x:y:quality"
         if ( strcmp( argv[ i + 1 ], "none" ) == 0 )
         {
            state->thumbnailConfig.enable = 0;
         }
         else
         {
            sscanf(argv[i + 1], "%d:%d:%d",
                   &state->thumbnailConfig.width,
                   &state->thumbnailConfig.height,
                   &state->thumbnailConfig.quality);
         }
         i++;
         break;

      case CommandDemoMode: // Run in demo mode - no capture
      {
         // Demo mode might have a timing parameter
         // so check if a) we have another parameter, b) its not the start of the next option
         if (i + 1 < argc  && argv[i+1][0] != '-')
         {
            if (sscanf(argv[i + 1], "%u", &state->demoInterval) == 1)
            {
               // TODO : What limits do we need for timeout?
               state->demoMode = 1;
               i++;
            }
            else
               valid = 0;
         }
         else
         {
            state->demoMode = 1;
         }

         break;
      }

      case CommandEncoding :
      {
         int len = strlen(argv[i + 1]);
         valid = 0;

         if (len)
         {
            int j;
            for (j=0; j<encoding_xref_size; j++)
            {
               if (strcmp(encoding_xref[j].format, argv[i+1]) == 0)
               {
                  state->encoding = encoding_xref[j].encoding;
                  valid = 1;
                  i++;
                  break;
               }
            }
         }
         break;
      }

      case CommandExifTag:
         if ( strcmp( argv[ i + 1 ], "none" ) == 0 )
         {
            state->enableExifTags = 0;
         }
         else
         {
            store_exif_tag(state, argv[i+1]);
         }
         i++;
         break;

      case CommandTimelapse:
         if (sscanf(argv[i + 1], "%u", &state->timelapse) != 1)
            valid = 0;
         else
         {
            if (state->timelapse)
               state->frameNextMethod = FRAME_NEXT_TIMELAPSE;
            else
               state->frameNextMethod = FRAME_NEXT_IMMEDIATELY;

            i++;
         }
         break;

      case CommandFullResPreview:
         state->fullResPreview = 1;
         break;

      case CommandKeypress: // Set keypress between capture mode
         state->frameNextMethod = FRAME_NEXT_KEYPRESS;

         if (state->timeout == -1)
            state->timeout = 0;

         break;

      case CommandSignal:   // Set SIGUSR1 & SIGUSR2 between capture mode
         state->frameNextMethod = FRAME_NEXT_SIGNAL;
         // Reenable the signal
         signal(SIGUSR1, default_signal_handler);
         signal(SIGUSR2, default_signal_handler);

         if (state->timeout == -1)
            state->timeout = 0;

         break;

      case CommandGL:
         state->useGL = 1;
         break;

      case CommandGLCapture:
         state->glCapture = 1;
         break;

      case CommandBurstMode:
         state->burstCaptureMode=1;
         break;

      case CommandRestartInterval:
      {
         if (sscanf(argv[i + 1], "%u", &state->restart_interval) == 1)
         {
            i++;
         }
         else
            valid = 0;
         break;
      }

      default:
      {
         // Try parsing for any image specific parameters
         // result indicates how many parameters were used up, 0,1,2
         // but we adjust by -1 as we have used one already
         const char *second_arg = (i + 1 < argc) ? argv[i + 1] : NULL;
         int parms_used = raspicamcontrol_parse_cmdline(&state->camera_parameters, &argv[i][1], second_arg);

         // Still unused, try common settings
         if (!parms_used)
            parms_used = raspicommonsettings_parse_cmdline(&state->common_settings, &argv[i][1], second_arg, &application_help_message);

         // Still unused, try preview settings
         if (!parms_used)
            parms_used = raspipreview_parse_cmdline(&state->preview_parameters, &argv[i][1], second_arg);

         // Still unused, try GL preview options
         if (!parms_used)
            parms_used = raspitex_parse_cmdline(&state->raspitex_state, &argv[i][1], second_arg);

         // If no parms were used, this must be a bad parameters
         if (!parms_used)
            valid = 0;
         else
            i += parms_used - 1;

         break;
      }
      }
   }

   /* GL preview parameters use preview parameters as defaults unless overriden */
   if (! state->raspitex_state.gl_win_defined)
   {
      state->raspitex_state.x       = state->preview_parameters.previewWindow.x;
      state->raspitex_state.y       = state->preview_parameters.previewWindow.y;
      state->raspitex_state.width   = state->preview_parameters.previewWindow.width;
      state->raspitex_state.height  = state->preview_parameters.previewWindow.height;
   }
   /* Also pass the preview information through so GL renderer can determine
    * the real resolution of the multi-media image */
   state->raspitex_state.preview_x       = state->preview_parameters.previewWindow.x;
   state->raspitex_state.preview_y       = state->preview_parameters.previewWindow.y;
   state->raspitex_state.preview_width   = state->preview_parameters.previewWindow.width;
   state->raspitex_state.preview_height  = state->preview_parameters.previewWindow.height;
   state->raspitex_state.opacity         = state->preview_parameters.opacity;
   state->raspitex_state.verbose         = state->common_settings.verbose;

   if (!valid)
   {
      fprintf(stderr, "Invalid command line option (%s)\n", argv[i-1]);
      return 1;
   }

   return 0;
}