#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ reg_desc; } ;
typedef  TYPE_1__ hb_stream_t ;
struct TYPE_9__ {int stream_type; scalar_t__* codec_name; int codec; int /*<<< orphan*/  codec_param; } ;
typedef  TYPE_2__ hb_pes_stream_t ;
struct TYPE_11__ {char const* name; } ;
struct TYPE_10__ {scalar_t__* name; } ;
typedef  TYPE_3__ AVCodec ;

/* Variables and functions */
 int HB_ACODEC_FF_MASK ; 
 scalar_t__ STR4_TO_UINT32 (char*) ; 
 TYPE_3__* avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 TYPE_6__* st2codec ; 
 int /*<<< orphan*/  strncpyupper (char*,scalar_t__*,int) ; 

__attribute__((used)) static const char *stream_type_name2(hb_stream_t *stream, hb_pes_stream_t *pes)
{
    static char codec_name_caps[80];

    if ( stream->reg_desc == STR4_TO_UINT32("HDMV") )
    {
        // Names for streams we know about.
        switch ( pes->stream_type )
        {
            case 0x80:
                return "BD LPCM";

            case 0x83:
                return "TrueHD";

            case 0x84:
                return "E-AC3";

            case 0x85:
                return "DTS-HD HRA";

            case 0x86:
                return "DTS-HD MA";

            default:
                break;
        }
    }
    if ( st2codec[pes->stream_type].name )
    {
        return st2codec[pes->stream_type].name;
    }
    if ( pes->codec_name[0] != 0 )
    {
        return pes->codec_name;
    }
    if ( pes->codec & HB_ACODEC_FF_MASK )
    {
        AVCodec * codec = avcodec_find_decoder( pes->codec_param );
        if ( codec && codec->name && codec->name[0] )
        {
            strncpyupper( codec_name_caps, codec->name, 80 );
            return codec_name_caps;
        }
    }
    return "Unknown";
}