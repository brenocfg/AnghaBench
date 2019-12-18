#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {float title_block_count; int stopped; scalar_t__ title; scalar_t__ cell; scalar_t__ chapter; int /*<<< orphan*/  dvdnav; int /*<<< orphan*/  list_dvd_chapter; } ;
typedef  TYPE_1__ hb_dvdnav_t ;
struct TYPE_7__ {TYPE_1__ dvdnav; } ;
typedef  TYPE_2__ hb_dvd_t ;
struct TYPE_8__ {scalar_t__ block_end; scalar_t__ block_start; scalar_t__ pgcn; int /*<<< orphan*/  pgn; } ;
typedef  TYPE_3__ hb_dvd_chapter_t ;

/* Variables and functions */
#define  DVDNAV_AUDIO_STREAM_CHANGE 140 
#define  DVDNAV_BLOCK_OK 139 
#define  DVDNAV_CELL_CHANGE 138 
#define  DVDNAV_HIGHLIGHT 137 
#define  DVDNAV_HOP_CHANNEL 136 
#define  DVDNAV_NAV_PACKET 135 
#define  DVDNAV_NOP 134 
#define  DVDNAV_SPU_CLUT_CHANGE 133 
#define  DVDNAV_SPU_STREAM_CHANGE 132 
 int DVDNAV_STATUS_ERR ; 
 scalar_t__ DVDNAV_STATUS_OK ; 
#define  DVDNAV_STILL_FRAME 131 
#define  DVDNAV_STOP 130 
#define  DVDNAV_VTS_CHANGE 129 
#define  DVDNAV_WAIT 128 
 int HB_DVD_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ dvdnav_current_title_program (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dvdnav_err_to_string (int /*<<< orphan*/ ) ; 
 int dvdnav_get_next_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ dvdnav_program_play (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvdnav_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ dvdnav_sector_search (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvdnav_still_skip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvdnav_wait_skip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 

__attribute__((used)) static int hb_dvdnav_seek( hb_dvd_t * e, float f )
{
    hb_dvdnav_t * d = &(e->dvdnav);
    uint64_t sector = f * d->title_block_count;
    int result, event, len;
    uint8_t buf[HB_DVD_READ_BUFFER_SIZE];
    int done = 0, ii;

    if (d->stopped)
    {
        return 0;
    }

    // XXX the current version of libdvdnav can't seek outside the current
    // PGC. Check if the place we're seeking to is in a different
    // PGC. Position there & adjust the offset if so.
    uint64_t pgc_offset = 0;
    uint64_t chap_offset = 0;
    hb_dvd_chapter_t *pgc_change = hb_list_item(d->list_dvd_chapter, 0 );
    for ( ii = 0; ii < hb_list_count( d->list_dvd_chapter ); ++ii )
    {
        hb_dvd_chapter_t *chapter = hb_list_item( d->list_dvd_chapter, ii );
        uint64_t chap_len = chapter->block_end - chapter->block_start + 1;

        if ( chapter->pgcn != pgc_change->pgcn )
        {
            // this chapter's in a different pgc from the previous - note the
            // change so we can make sector offset's be pgc relative.
            pgc_offset = chap_offset;
            pgc_change = chapter;
        }
        if ( chap_offset <= sector && sector < chap_offset + chap_len )
        {
            // this chapter contains the sector we want - see if it's in a
            // different pgc than the one we're currently in.
            int32_t title, pgcn, pgn;
            if (dvdnav_current_title_program( d->dvdnav, &title, &pgcn, &pgn ) != DVDNAV_STATUS_OK)
                hb_log("dvdnav cur pgcn err: %s", dvdnav_err_to_string(d->dvdnav));
            // If we find ourselves in a new title, it means a title
            // transition was made while reading data.  Jumping between
            // titles can cause the vm to get into a bad state.  So
            // reset the vm in this case.
            if ( d->title != title )
                dvdnav_reset( d->dvdnav );

            if ( d->title != title || chapter->pgcn != pgcn )
            {
                // this chapter is in a different pgc - switch to it.
                if (dvdnav_program_play(d->dvdnav, d->title, chapter->pgcn, chapter->pgn) != DVDNAV_STATUS_OK)
                    hb_log("dvdnav prog play err: %s", dvdnav_err_to_string(d->dvdnav));
            }
            // seek sectors are pgc-relative so remove the pgc start sector.
            sector -= pgc_offset;
            break;
        }
        chap_offset += chap_len;
    }

    // dvdnav will not let you seek or poll current position
    // till it reaches a certain point in parsing.  so we
    // have to get blocks until we reach a cell
    // Put an arbitrary limit of 100 blocks on how long we search
    for (ii = 0; ii < 100 && !done; ii++)
    {
        result = dvdnav_get_next_block( d->dvdnav, buf, &event, &len );
        if ( result == DVDNAV_STATUS_ERR )
        {
            hb_error("dvdnav: Read Error, %s", dvdnav_err_to_string(d->dvdnav));
            return 0;
        }
        switch ( event )
        {
        case DVDNAV_BLOCK_OK:
        case DVDNAV_CELL_CHANGE:
            done = 1;
            break;

        case DVDNAV_STILL_FRAME:
            dvdnav_still_skip( d->dvdnav );
            break;

        case DVDNAV_WAIT:
            dvdnav_wait_skip( d->dvdnav );
            break;

        case DVDNAV_STOP:
            hb_log("dvdnav: stop encountered during seek");
            d->stopped = 1;
            return 0;

        case DVDNAV_HOP_CHANNEL:
        case DVDNAV_NAV_PACKET:
        case DVDNAV_VTS_CHANGE:
        case DVDNAV_HIGHLIGHT:
        case DVDNAV_AUDIO_STREAM_CHANGE:
        case DVDNAV_SPU_STREAM_CHANGE:
        case DVDNAV_SPU_CLUT_CHANGE:
        case DVDNAV_NOP:
        default:
            break;
        }
    }

    if (dvdnav_sector_search(d->dvdnav, sector, SEEK_SET) != DVDNAV_STATUS_OK)
    {
        hb_error( "dvd: dvdnav_sector_search failed - %s",
                  dvdnav_err_to_string(d->dvdnav) );
        return 0;
    }
    d->chapter = 0;
    d->cell = 0;
    return 1;
}