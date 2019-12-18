#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_22__ {int pack_len; size_t cell_cur; size_t cell_end; scalar_t__ next_vobu; int cell_next; int in_cell; int cell_overlap; int in_sync; scalar_t__ cur_cell_id; scalar_t__ cur_vob_id; int block; int title_start; int title_block_count; int title_end; int /*<<< orphan*/  file; TYPE_4__* pgc; int /*<<< orphan*/  h; } ;
typedef  TYPE_6__ hb_dvdread_t ;
struct TYPE_23__ {TYPE_6__ dvdread; } ;
typedef  TYPE_7__ hb_dvd_t ;
struct TYPE_21__ {int /*<<< orphan*/  new_chap; } ;
struct TYPE_24__ {TYPE_5__ s; int /*<<< orphan*/ * data; } ;
typedef  TYPE_8__ hb_buffer_t ;
struct TYPE_18__ {int next_vobu; int next_video; int prev_vobu; } ;
struct TYPE_17__ {scalar_t__ vobu_vob_idn; scalar_t__ vobu_c_idn; int nv_pck_lbn; int vobu_ea; } ;
struct TYPE_25__ {TYPE_2__ vobu_sri; TYPE_1__ dsi_gi; } ;
typedef  TYPE_9__ dsi_t ;
struct TYPE_20__ {TYPE_3__* cell_playback; } ;
struct TYPE_19__ {size_t first_sector; scalar_t__ last_sector; } ;

/* Variables and functions */
 size_t DSI_START_BYTE ; 
 int DVDReadBlocks (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindNextCell (TYPE_6__*) ; 
 int /*<<< orphan*/  HB_DVD_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  HB_ERROR_READ ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_8__**) ; 
 TYPE_8__* hb_buffer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  hb_dvdread_is_break (TYPE_6__*) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/  hb_log (char*,size_t,...) ; 
 int /*<<< orphan*/  hb_set_work_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_nav_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  navRead_DSI (TYPE_9__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_buffer_t * hb_dvdread_read( hb_dvd_t * e )
{
    hb_dvdread_t *d = &(e->dvdread);
    hb_buffer_t *b = hb_buffer_init( HB_DVD_READ_BUFFER_SIZE );
 top:
    if( !d->pack_len )
    {
        /* New pack */
        dsi_t dsi_pack;
        int   error = 0;

        // if we've just finished the last cell of the title we don't
        // want to read another block because our next_vobu pointer
        // is probably invalid. Just return 'no data' & our caller
        // should check and discover we're at eof.
        if ( d->cell_cur > d->cell_end )
        {
            hb_buffer_close( &b );
            return NULL;
        }

        for( ;; )
        {
            int block, pack_len, next_vobu, read_retry;

            for( read_retry = 1; read_retry < 1024; read_retry++ )
            {
                if( DVDReadBlocks( d->file, d->next_vobu, 1, b->data ) == 1 )
                {
                    /*
                     * Successful read.
                     */
                    if( read_retry > 1 && !is_nav_pack( b->data) )
                    {
                        // But wasn't a nav pack, so carry on looking
                        read_retry = 1;
                        d->next_vobu++;
                        continue;
                    }
                    break;
                } else {
                    // First retry the same block, then try the next one,
                    // adjust the skip increment upwards so that we can skip
                    // large sections of bad blocks more efficiently (at the
                    // cost of some missed good blocks at the end).
                    hb_log( "dvd: vobu read error blk %d - skipping to next blk incr %d",
                            d->next_vobu, (read_retry * 10));
                    d->next_vobu += (read_retry * 10);
                }

            }

            if( read_retry == 1024 )
            {
                // That's too many bad blocks, jump to the start of the
                // next cell.
                hb_log( "dvd: vobu read error blk %d - skipping to cell %d",
                        d->next_vobu, d->cell_next );
                d->cell_cur  = d->cell_next;
                if ( d->cell_cur > d->cell_end )
                {
                    hb_buffer_close( &b );
                    hb_set_work_error(d->h, HB_ERROR_READ);
                    return NULL;
                }
                d->in_cell = 0;
                d->next_vobu = d->pgc->cell_playback[d->cell_cur].first_sector;
                FindNextCell( d );
                d->cell_overlap = 1;
                continue;
            }

            if ( !is_nav_pack( b->data ) ) {
                (d->next_vobu)++;
                if( d->in_sync == 1 ) {
                    hb_log("dvd: Lost sync, searching for NAV pack at blk %d",
                           d->next_vobu);
                    d->in_sync = 0;
                }
                continue;
            }

            navRead_DSI( &dsi_pack, &b->data[DSI_START_BYTE] );

            if ( d->in_sync == 0 && d->cur_cell_id &&
                 (d->cur_vob_id != dsi_pack.dsi_gi.vobu_vob_idn ||
                  d->cur_cell_id != dsi_pack.dsi_gi.vobu_c_idn ) )
            {
                // We walked out of the cell we're supposed to be in.
                // If we're not at the start of our next cell go there.
                hb_log("dvd: left cell %d (%u,%u) for (%u,%u) at block %u",
                       d->cell_cur, d->cur_vob_id, d->cur_cell_id,
                       dsi_pack.dsi_gi.vobu_vob_idn, dsi_pack.dsi_gi.vobu_c_idn,
                       d->next_vobu );
                if ( d->next_vobu != d->pgc->cell_playback[d->cell_next].first_sector )
                {
                    d->next_vobu = d->pgc->cell_playback[d->cell_next].first_sector;
                    d->cur_cell_id = 0;
                    continue;
                }
            }

            block     = dsi_pack.dsi_gi.nv_pck_lbn;
            pack_len  = dsi_pack.dsi_gi.vobu_ea;

            // There are a total of 21 next vobu offsets (and 21 prev_vobu
            // offsets) in the navpack SRI structure. The primary one is
            // 'next_vobu' which is the offset (in dvd blocks) from the current
            // block to the start of the next vobu. If the block at 'next_vobu'
            // can't be read, 'next_video' is the offset to the vobu closest to it.
            // The other 19 offsets are vobus at successively longer distances from
            // the current block (this is so that a hardware player can do
            // adaptive error recovery to skip over a bad spot on the disk). In all
            // these offsets the high bit is set to indicate when it contains a
            // valid offset. The next bit (2^30) is set to indicate that there's
            // another valid offset in the SRI that's closer to the current block.
            // A hardware player uses these bits to chose the closest valid offset
            // and uses that as its next vobu. (Some mastering schemes appear to
            // put a bogus offset in next_vobu with the 2^30 bit set & the
            // correct offset in next_video. This works fine in hardware players
            // but will mess up software that doesn't implement the full next
            // vobu decision logic.) In addition to the flag bits there's a
            // reserved value of the offset that indicates 'no next vobu' (which
            // indicates the end of a cell). But having no next vobu pointer with a
            // 'valid' bit set also indicates end of cell. Different mastering
            // schemes seem to use all possible combinations of the flag bits
            // and reserved values to indicate end of cell so we have to check
            // them all or we'll get a disk read error from following an
            // invalid offset.
            uint32_t next_ptr = dsi_pack.vobu_sri.next_vobu;
            if ( ( next_ptr & ( 1 << 31 ) ) == 0  ||
                 ( next_ptr & ( 1 << 30 ) ) != 0 ||
                 ( next_ptr & 0x3fffffff ) == 0x3fffffff )
            {
                next_ptr = dsi_pack.vobu_sri.next_video;
                if ( ( next_ptr & ( 1 << 31 ) ) == 0 ||
                     ( next_ptr & 0x3fffffff ) == 0x3fffffff )
                {
                    // don't have a valid forward pointer - assume end-of-cell
                    d->block     = block;
                    d->pack_len  = pack_len;
                    break;
                }
            }
            next_vobu = block + ( next_ptr & 0x3fffffff );

            if( pack_len >  0    &&
                pack_len <  1024 &&
                block    >= d->next_vobu &&
                ( block <= d->title_start + d->title_block_count ||
                  block <= d->title_end ) )
            {
                d->block     = block;
                d->pack_len  = pack_len;
                d->next_vobu = next_vobu;
                break;
            }

            /* Wasn't a valid VOBU, try next block */
            if( ++error > 1024 )
            {
                hb_error( "dvd: couldn't find a VOBU after 1024 blocks" );
                hb_buffer_close( &b );
                hb_set_work_error(d->h, HB_ERROR_READ);
                return NULL;
            }

            (d->next_vobu)++;
        }

        if( d->in_sync == 0 || d->in_sync == 2 )
        {
            if( d->in_sync == 0 )
            {
                hb_log( "dvd: In sync with DVD at block %d", d->block );
            }
            d->in_sync = 1;
        }

        // Revert the cell overlap, and check for a chapter break
        // If this cell is zero length (prev_vobu & next_vobu both
        // set to END_OF_CELL) we need to check for beginning of
        // cell before checking for end or we'll advance to the next
        // cell too early and fail to generate a chapter mark when this
        // cell starts a chapter.
        if( ( dsi_pack.vobu_sri.prev_vobu & (1 << 31 ) ) == 0 ||
            ( dsi_pack.vobu_sri.prev_vobu & 0x3fffffff ) == 0x3fffffff )
        {
            // A vobu that's not at the start of a cell can have an
            // EOC prev pointer (this seems to be associated with some
            // sort of drm). The rest of the content in the cell may be
            // booby-trapped so treat this like an end-of-cell rather
            // than a beginning of cell.
            if ( d->pgc->cell_playback[d->cell_cur].first_sector < dsi_pack.dsi_gi.nv_pck_lbn &&
                 d->pgc->cell_playback[d->cell_cur].last_sector >= dsi_pack.dsi_gi.nv_pck_lbn )
            {
                hb_log( "dvd: null prev_vobu in cell %d at block %d", d->cell_cur,
                        d->block );
                // treat like end-of-cell then go directly to start of next cell.
                d->cell_cur  = d->cell_next;
                d->in_cell = 0;
                d->next_vobu = d->pgc->cell_playback[d->cell_cur].first_sector;
                FindNextCell( d );
                d->cell_overlap = 1;
                goto top;
            }
            else
            {
                if ( d->block != d->pgc->cell_playback[d->cell_cur].first_sector )
                {
                    hb_deep_log(3, "dvd: beginning of cell %d at block %d", d->cell_cur,
                           d->block);
                }
                if( d->in_cell )
                {
                    hb_error( "dvd: assuming missed end of cell %d at block %d", d->cell_cur, d->block );
                    d->cell_cur  = d->cell_next;
                    d->next_vobu = d->pgc->cell_playback[d->cell_cur].first_sector;
                    FindNextCell( d );
                    d->cell_overlap = 1;
                    d->in_cell = 0;
                } else {
                    d->in_cell = 1;
                }
                d->cur_vob_id = dsi_pack.dsi_gi.vobu_vob_idn;
                d->cur_cell_id = dsi_pack.dsi_gi.vobu_c_idn;

                d->cell_overlap = 0;
            }
        }

        if( ( dsi_pack.vobu_sri.next_vobu & (1 << 31 ) ) == 0 ||
            ( dsi_pack.vobu_sri.next_vobu & 0x3fffffff ) == 0x3fffffff )
        {
            if ( d->block <= d->pgc->cell_playback[d->cell_cur].first_sector ||
                 d->block > d->pgc->cell_playback[d->cell_cur].last_sector )
            {
                hb_deep_log(3, "dvd: end of cell %d at block %d", d->cell_cur,
                        d->block);
            }
            d->cell_cur  = d->cell_next;
            d->in_cell = 0;
            d->next_vobu = d->pgc->cell_playback[d->cell_cur].first_sector;
            FindNextCell( d );
            d->cell_overlap = 1;

        }
    }
    else
    {
        if( DVDReadBlocks( d->file, d->block, 1, b->data ) != 1 )
        {
            // this may be a real DVD error or may be DRM. Either way
            // we don't want to quit because of one bad block so set
            // things up so we'll advance to the next vobu and recurse.
            hb_error( "dvd: DVDReadBlocks failed (%d), skipping to vobu %u",
                      d->block, d->next_vobu );
            d->pack_len = 0;
            goto top;  /* XXX need to restructure this routine & avoid goto */
        }
        d->pack_len--;
    }
    if (b != NULL)
    {
        b->s.new_chap = hb_dvdread_is_break( d );
    }

    d->block++;

    return b;
}