#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_7__ {char const* uri; char const* vformat; int tunneling; int zero_copy; int opaque; int /*<<< orphan*/  camera_num; int /*<<< orphan*/  focus_test; int /*<<< orphan*/  bit_rate; TYPE_1__ frame_rate; int /*<<< orphan*/  change; int /*<<< orphan*/  seconds_per_change; int /*<<< orphan*/  display_area; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAM_FOCUS_EDOF ; 
 TYPE_4__ camcorder_behaviour ; 
 size_t countof (TYPE_2__*) ; 
 TYPE_2__* mmalcam_change_table ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sleepy_time ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  test_mmalcam_parse_rect (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_parse_cmdline(int argc, const char **argv)
{
   int i;
   int passed_options = 0;

   /* Parse the command line arguments */
   for(i = 1; i < argc; i++)
   {
      if (!argv[i]) continue;

      if (passed_options || argv[i][0] != '-')
      {
         /* Non-option argument */
         continue;
      }

      /* We are now dealing with command line options */
      switch(argv[i][1])
      {
      case '-': passed_options = 1; break;
      case 'h': goto usage;
      case 'o': if (i+1 >= argc) goto invalid_option;
         camcorder_behaviour.uri = argv[++i];
         break;
      case 'v': if (i+1 >= argc) goto invalid_option;
         camcorder_behaviour.vformat = argv[i+1];
         break;
      case 'r': if (i+1 >= argc) goto invalid_option;
         if (!test_mmalcam_parse_rect(argv[i+1], &camcorder_behaviour.display_area)) goto invalid_option;
         i++;
         break;
      case 'c': if (i+2 >= argc) goto invalid_option;
         {
            uint32_t table_index;

            if (sscanf(argv[i+1], "%u", &camcorder_behaviour.seconds_per_change) != 1) goto invalid_option;

            for (table_index = 0; table_index < countof(mmalcam_change_table); table_index++)
               if (strcmp(mmalcam_change_table[table_index].name, argv[i+2]) == 0)
                  break;
            if (table_index >= countof(mmalcam_change_table)) goto invalid_option;

            camcorder_behaviour.change = mmalcam_change_table[table_index].value;
         }
         break;
      case 't': if (i+1 >= argc) goto invalid_option;
         if (sscanf(argv[i+1], "%u", &sleepy_time) != 1) goto invalid_option;
         i++;
         break;
      case 'f': if (i+1 >= argc) goto invalid_option;
         camcorder_behaviour.frame_rate.den = 1;
         if (sscanf(argv[i+1], "%u/%u", &camcorder_behaviour.frame_rate.num, &camcorder_behaviour.frame_rate.den) == 0) goto invalid_option;
         i++;
         break;
      case 'x': camcorder_behaviour.tunneling = 1; break;
      case 'z': camcorder_behaviour.zero_copy = (argv[i][2] != '!'); break;
      case 'O': camcorder_behaviour.opaque = 1; break;
      case 'b': if (i+1 >= argc) goto invalid_option;
         if (sscanf(argv[i+1], "%u", &camcorder_behaviour.bit_rate) == 0) goto invalid_option;
         i++;
         break;
      case 'a': if (i+1 >= argc) goto invalid_option;
         if (sscanf(argv[i+1], "%u", &camcorder_behaviour.focus_test) == 0) goto invalid_option;
         if (camcorder_behaviour.focus_test > MMAL_PARAM_FOCUS_EDOF) goto invalid_option;
         i++;
         break;
      case 'n': if (i+1 >= argc) goto invalid_option;
         if (sscanf(argv[i+1], "%u", &camcorder_behaviour.camera_num) == 0) goto invalid_option;
         i++;
         break;
      default: goto invalid_option;
      }
      continue;
   }

   return 0;

 invalid_option:
   printf("invalid command line option (%s)\n", argv[i]);

 usage:
   {
      const char *program;

      program = strrchr(argv[0], '\\');
      if (program)
         program++;
      else
      {
         program = strrchr(argv[0], '/');
         if (program)
            program++;
         else
            program = argv[0];
      }
      printf("usage: %s [options]\n", program);
      printf("options list:\n");
      printf(" -h          : help\n");
      printf(" -o <file>   : write encoded output to <file>\n");
      printf(" -v <format> : set video resolution and encoding format (defaults to '1280x720:h264')\n");
      printf(" -r <r>      : put viewfinder at position <r>, given as x,y,width,height\n");
      printf(" -c <n> <x>  : change camera parameter every <n> seconds.\n");
      printf("                The parameter changed is defined by <x>, one of\n");
      printf("                image_effect, rotation, zoom, focus, hdr, drc, contrast,\n");
      printf("                brightness, saturation, sharpness\n");
      printf(" -t <n>      : operate camera for <n> seconds\n");
      printf(" -f <n>[/<d>]: set camera frame rate to <n>/<d>, where <d> is 1 if not given\n");
      printf(" -x          : use tunneling\n");
      printf(" -z          : use zero copy buffers (default)\n");
      printf(" -z!         : use full copy buffers\n");
      printf(" -O          : use opaque images\n");
      printf(" -b <n>      : use <n> as the bitrate (bits/s)\n");
      printf(" -a <n>      : Set to focus mode <n> (autofocus will cycle). Use MMAL_PARAM_FOCUS_T values.\n");
      printf(" -n <n>      : Set camera number <n>. Use MMAL_PARAMETER_CAMERA_NUM values.\n");
   }
   return 1;
}