#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int width; int height; int palette_set; int /*<<< orphan*/ * palette; } ;
typedef  TYPE_1__ hb_subtitle_t ;
struct TYPE_6__ {int extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_rgb2yuv (int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,int*,int*,...) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int ffmpeg_parse_vobsub_extradata_mkv( AVCodecParameters *codecpar,
                                              hb_subtitle_t *subtitle )
{
    // lines = (string) codecpar->extradata;
    char *lines = malloc( codecpar->extradata_size + 1 );
    if ( lines == NULL )
        return 1;
    memcpy( lines, codecpar->extradata, codecpar->extradata_size );
    lines[codecpar->extradata_size] = '\0';

    uint32_t rgb[16];
    int gotPalette = 0;
    int gotDimensions = 0;

    char *curLine, *curLine_parserData;
    for ( curLine = strtok_r( lines, "\n", &curLine_parserData );
          curLine;
          curLine = strtok_r( NULL, "\n", &curLine_parserData ) )
    {
        if (!gotPalette)
        {
            int numElementsRead = sscanf(curLine, "palette: "
                "%06x, %06x, %06x, %06x, "
                "%06x, %06x, %06x, %06x, "
                "%06x, %06x, %06x, %06x, "
                "%06x, %06x, %06x, %06x",
                &rgb[0],  &rgb[1],  &rgb[2],  &rgb[3],
                &rgb[4],  &rgb[5],  &rgb[6],  &rgb[7],
                &rgb[8],  &rgb[9],  &rgb[10], &rgb[11],
                &rgb[12], &rgb[13], &rgb[14], &rgb[15]);

            if (numElementsRead == 16) {
                gotPalette = 1;
            }
        }
        if (!gotDimensions)
        {
            int numElementsRead = sscanf(curLine, "size: %dx%d",
                &subtitle->width, &subtitle->height);

            if (numElementsRead == 2) {
                gotDimensions = 1;
            }
        }
        if (gotPalette && gotDimensions)
            break;
    }

    if (subtitle->width == 0 || subtitle->height == 0)
    {
        subtitle->width = 720;
        subtitle->height = 480;
    }

    free( lines );

    if ( gotPalette )
    {
        int i;
        for (i=0; i<16; i++)
            subtitle->palette[i] = hb_rgb2yuv(rgb[i]);
        subtitle->palette_set = 1;
        return 0;
    }
    else
    {
        return 1;
    }
}