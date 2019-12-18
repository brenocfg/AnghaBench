#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int PCR_PID; } ;
struct TYPE_9__ {TYPE_2__* title; TYPE_1__ pmt_info; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_10__ {int id; } ;
typedef  TYPE_4__ hb_audio_t ;
struct TYPE_8__ {int /*<<< orphan*/  list_audio; } ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audio_inactive( hb_stream_t *stream, int id, int stream_id_ext )
{
    if ( id < 0 )
    {
        // PID declared inactive by hb_stream_title_scan
        return 1;
    }
    if ( id == stream->pmt_info.PCR_PID )
    {
        // PCR PID is always active
        return 0;
    }

    int i;
    for ( i = 0; i < hb_list_count( stream->title->list_audio ); ++i )
    {
        hb_audio_t *audio = hb_list_item( stream->title->list_audio, i );
        if ( audio->id == ((stream_id_ext << 16) | id) )
        {
            return 0;
        }
    }
    return 1;
}