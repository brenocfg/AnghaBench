#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; scalar_t__ start; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_2__ hb_buffer_t ;

/* Variables and functions */
 int BT ; 
 int BTB_PROG ; 
 int BT_PROG ; 
 int PROGRESSIVE ; 
 int REPEAT_FIRST ; 
 int TB ; 
 int TBT_PROG ; 
 int TB_PROG ; 
 int TOP_FIRST ; 
 int /*<<< orphan*/  hb_log (char*,float) ; 

__attribute__((used)) static void checkCadence( int * cadence, hb_buffer_t * buf )
{
    /*  Rotate the cadence tracking. */
    int i = 0;
    for (i = 11; i > 0; i--)
    {
        cadence[i] = cadence[i-1];
    }

    if (!(buf->s.flags & PROGRESSIVE) && !(buf->s.flags & TOP_FIRST))
    {
        /* Not progressive, not top first...
           That means it's probably bottom
           first, 2 fields displayed.
        */
        //hb_log("MPEG2 Flag: Bottom field first, 2 fields displayed.");
        cadence[0] = BT;
    }
    else if (!(buf->s.flags & PROGRESSIVE) && (buf->s.flags & TOP_FIRST))
    {
        /* Not progressive, top is first,
           Two fields displayed.
        */
        //hb_log("MPEG2 Flag: Top field first, 2 fields displayed.");
        cadence[0] = TB;
    }
    else if ((buf->s.flags & PROGRESSIVE) &&
             !(buf->s.flags & TOP_FIRST) && !(buf->s.flags & REPEAT_FIRST))
    {
        /* Progressive, but noting else.
           That means Bottom first,
           2 fields displayed.
        */
        //hb_log("MPEG2 Flag: Progressive. Bottom field first, 2 fields displayed.");
        cadence[0] = BT_PROG;
    }
    else if ((buf->s.flags & PROGRESSIVE) &&
             !(buf->s.flags & TOP_FIRST) && (buf->s.flags & REPEAT_FIRST))
    {
        /* Progressive, and repeat. .
           That means Bottom first,
           3 fields displayed.
        */
        //hb_log("MPEG2 Flag: Progressive repeat. Bottom field first, 3 fields displayed.");
        cadence[0] = BTB_PROG;
    }
    else if ((buf->s.flags & PROGRESSIVE) &&
             (buf->s.flags & TOP_FIRST) && !(buf->s.flags & REPEAT_FIRST))
    {
        /* Progressive, top first.
           That means top first,
           2 fields displayed.
        */
        //hb_log("MPEG2 Flag: Progressive. Top field first, 2 fields displayed.");
        cadence[0] = TB_PROG;
    }
    else if ((buf->s.flags & PROGRESSIVE) &&
             (buf->s.flags & TOP_FIRST) && (buf->s.flags & REPEAT_FIRST))
    {
        /* Progressive, top, repeat.
           That means top first,
           3 fields displayed.
        */
        //hb_log("MPEG2 Flag: Progressive repeat. Top field first, 3 fields displayed.");
        cadence[0] = TBT_PROG;
    }

    if ((cadence[2] <= TB) && (cadence[1] <= TB) &&
        (cadence[0] > TB) && (cadence[11]))
    {
        hb_log("%fs: Video -> Film", (float)buf->s.start / 90000);
    }
    if ((cadence[2] > TB) && (cadence[1] <= TB) &&
        (cadence[0] <= TB) && (cadence[11]))
    {
        hb_log("%fs: Film -> Video", (float)buf->s.start / 90000);
    }
}