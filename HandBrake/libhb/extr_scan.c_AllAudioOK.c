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
struct TYPE_9__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_3__ hb_title_t ;
struct TYPE_7__ {scalar_t__ bitrate; } ;
struct TYPE_8__ {TYPE_1__ in; } ;
struct TYPE_10__ {TYPE_2__ config; } ;
typedef  TYPE_4__ hb_audio_t ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int  AllAudioOK( hb_title_t * title )
{
    int i;
    hb_audio_t * audio;

    for( i = 0; i < hb_list_count( title->list_audio ); i++ )
    {
        audio = hb_list_item( title->list_audio, i );
        if( audio->config.in.bitrate == 0 )
        {
            return 0;
        }
    }
    return 1;
}