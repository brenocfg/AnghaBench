#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int index; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_11__ {scalar_t__ cell; int /*<<< orphan*/  chapter; scalar_t__ stopped; int /*<<< orphan*/  dvdnav; int /*<<< orphan*/  list_dvd_chapter; } ;
typedef  TYPE_2__ hb_dvdnav_t ;
struct TYPE_12__ {TYPE_2__ dvdnav; } ;
typedef  TYPE_3__ hb_dvd_t ;
struct TYPE_13__ {int /*<<< orphan*/  pgn; int /*<<< orphan*/  pgcn; } ;
typedef  TYPE_4__ hb_dvd_chapter_t ;
typedef  scalar_t__ dvdnav_status_t ;

/* Variables and functions */
 scalar_t__ DVDNAV_STATUS_OK ; 
 int /*<<< orphan*/  TitleOpenIfo (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dvdnav_err_to_string (int /*<<< orphan*/ ) ; 
 scalar_t__ dvdnav_part_play (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ dvdnav_program_play (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvdnav_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_dvdnav_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hb_dvdnav_start( hb_dvd_t * e, hb_title_t *title, int c )
{
    hb_dvdnav_t * d = &(e->dvdnav);
    int t = title->index;
    hb_dvd_chapter_t *chapter;
    dvdnav_status_t result;

    if ( d->stopped && !hb_dvdnav_reset(d) )
    {
        return 0;
    }
    if (!TitleOpenIfo(d, t))
    {
        return 0;
    }
    dvdnav_reset( d->dvdnav );
    chapter = hb_list_item( d->list_dvd_chapter, c - 1);
    if (chapter != NULL)
        result = dvdnav_program_play(d->dvdnav, t, chapter->pgcn, chapter->pgn);
    else
        result = dvdnav_part_play(d->dvdnav, t, 1);
    if (result != DVDNAV_STATUS_OK)
    {
        hb_error( "dvd: dvdnav_*_play failed - %s",
                  dvdnav_err_to_string(d->dvdnav) );
        return 0;
    }
    d->stopped = 0;
    d->chapter = 0;
    d->cell = 0;
    return 1;
}