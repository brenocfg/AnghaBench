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
#define  CC608SUB 139 
#define  CC708SUB 138 
#define  HB_MUX_AV_MKV 137 
#define  HB_MUX_AV_MP4 136 
#define  HB_MUX_AV_WEBM 135 
#define  IMPORTSRT 134 
#define  IMPORTSSA 133 
#define  PGSSUB 132 
#define  SSASUB 131 
#define  TX3GSUB 130 
#define  UTF8SUB 129 
#define  VOBSUB 128 
 int /*<<< orphan*/  hb_error (char*,int) ; 

int hb_subtitle_can_pass( int source, int mux )
{
    switch (mux)
    {
        case HB_MUX_AV_MKV:
            switch( source )
            {
                case PGSSUB:
                case VOBSUB:
                case SSASUB:
                case UTF8SUB:
                case TX3GSUB:
                case CC608SUB:
                case CC708SUB:
                case IMPORTSRT:
                case IMPORTSSA:
                    return 1;

                default:
                    return 0;
            } break;

        case HB_MUX_AV_MP4:
            switch( source )
            {
                case VOBSUB:
                case SSASUB:
                case UTF8SUB:
                case TX3GSUB:
                case CC608SUB:
                case CC708SUB:
                case IMPORTSRT:
                case IMPORTSSA:
                    return 1;

                default:
                    return 0;
            } break;

        // webm can't support subtitles unless they're burned.
        // there's ambiguity in the spec about WebVTT... TODO
        case HB_MUX_AV_WEBM:
            return 0;
        default:
            // Internal error. Should never get here.
            hb_error("internal error.  Bad mux %d\n", mux);
            return 0;
    }
}