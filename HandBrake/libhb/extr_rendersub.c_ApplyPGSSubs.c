#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  sub_list; } ;
typedef  TYPE_3__ hb_filter_private_t ;
struct TYPE_18__ {scalar_t__ start; } ;
struct TYPE_17__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_20__ {TYPE_2__ s; TYPE_1__ f; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ApplySub (TYPE_3__*,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* ScaleSubtitle (TYPE_3__*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_4__**) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_list_rem (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void ApplyPGSSubs( hb_filter_private_t * pv, hb_buffer_t * buf )
{
    int index;
    hb_buffer_t * old_sub;
    hb_buffer_t * sub;

    // Each PGS subtitle supersedes anything that preceded it.
    // Find the active subtitle (if there is one), and delete
    // everything before it.
    for( index = hb_list_count( pv->sub_list ) - 1; index > 0; index-- )
    {
        sub = hb_list_item( pv->sub_list, index);
        if ( sub->s.start <= buf->s.start )
        {
            while ( index > 0 )
            {
                old_sub = hb_list_item( pv->sub_list, index - 1);
                hb_list_rem( pv->sub_list, old_sub );
                hb_buffer_close( &old_sub );
                index--;
            }
        }
    }

    // Some PGS subtitles have no content and only serve to clear
    // the screen. If any of these are at the front of our list,
    // we can now get rid of them.
    while ( hb_list_count( pv->sub_list ) > 0 )
    {
        sub = hb_list_item( pv->sub_list, 0 );
        if (sub->f.width != 0 && sub->f.height != 0)
            break;

        hb_list_rem( pv->sub_list, sub );
        hb_buffer_close( &sub );
    }

    // Check to see if there's an active subtitle, and apply it.
    if ( hb_list_count( pv->sub_list ) > 0)
    {
        sub = hb_list_item( pv->sub_list, 0 );
        if ( sub->s.start <= buf->s.start )
        {
            hb_buffer_t *scaled = ScaleSubtitle(pv, sub, buf);
            ApplySub( pv, buf, scaled );
            hb_buffer_close(&scaled);
        }
    }
}