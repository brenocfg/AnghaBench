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
struct TYPE_8__ {scalar_t__ new_chap; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ video; } ;
typedef  TYPE_3__ sync_stream_t ;
struct TYPE_7__ {scalar_t__ new_chap; } ;
struct TYPE_10__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ SYNC_TYPE_VIDEO ; 

__attribute__((used)) static void restoreChap( sync_stream_t * stream, hb_buffer_t * buf )
{
    if (stream->type != SYNC_TYPE_VIDEO || buf == NULL)
    {
        return;
    }
    if (stream->video.new_chap > 0 && buf->s.new_chap <= 0)
    {
        buf->s.new_chap = stream->video.new_chap;
        stream->video.new_chap = 0;
    }
}