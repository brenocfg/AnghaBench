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

/* Variables and functions */
 int /*<<< orphan*/  LOG_STD (char*) ; 

__attribute__((used)) static void show_usage( void )
{
   LOG_STD( "Usage: tvservice [OPTION]..." );
   LOG_STD( "  -p, --preferred                   Power on HDMI with preferred settings" );
   LOG_STD( "  -e, --explicit=\"GROUP MODE DRIVE\" Power on HDMI with explicit GROUP (CEA, DMT, CEA_3D_SBS, CEA_3D_TB, CEA_3D_FP, CEA_3D_FS)\n"
            "                                      MODE (see --modes) and DRIVE (HDMI, DVI)" );
   LOG_STD( "  -t, --ntsc                        Use NTSC frequency for HDMI mode (e.g. 59.94Hz rather than 60Hz)" );
   LOG_STD( "  -c, --sdtvon=\"MODE ASPECT [P]\"    Power on SDTV with MODE (PAL or NTSC) and ASPECT (4:3 14:9 or 16:9) Add P for progressive" );
   LOG_STD( "  -o, --off                         Power off the display" );
   LOG_STD( "  -m, --modes=GROUP                 Get supported modes for GROUP (CEA, DMT)" );
   LOG_STD( "  -M, --monitor                     Monitor HDMI events" );
   LOG_STD( "  -s, --status                      Get HDMI status" );
   LOG_STD( "  -a, --audio                       Get supported audio information" );
   LOG_STD( "  -d, --dumpedid <filename>         Dump EDID information to file" );
   LOG_STD( "  -j, --json                        Use JSON format for --modes output" );
   LOG_STD( "  -n, --name                        Print the device ID from EDID" );
   LOG_STD( "  -h, --help                        Print this information" );
}