#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
typedef  int uInt ;
struct TYPE_14__ {scalar_t__ status; int last_flush; int w_bits; int level; scalar_t__ strstart; scalar_t__ pending; scalar_t__ lookahead; int noheader; TYPE_1__* strm; } ;
typedef  TYPE_2__ deflate_state ;
typedef  scalar_t__ block_state ;
struct TYPE_13__ {scalar_t__ avail_in; scalar_t__ avail_out; int adler; int /*<<< orphan*/ * next_in; int /*<<< orphan*/ * state; } ;
struct TYPE_12__ {scalar_t__ (* func ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int,char*) ; 
 scalar_t__ BUSY_STATE ; 
 int /*<<< orphan*/  CLEAR_HASH (TYPE_2__*) ; 
 scalar_t__ FINISH_STATE ; 
 scalar_t__ INIT_STATE ; 
 int PRESET_DICT ; 
 int Z_BUF_ERROR ; 
 int Z_DEFLATED ; 
 int Z_FINISH ; 
 int Z_FULL_FLUSH ; 
 int Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_PACKET_FLUSH ; 
 int Z_PARTIAL_FLUSH ; 
 int Z_STREAM_END ; 
 int Z_STREAM_ERROR ; 
 scalar_t__ block_done ; 
 TYPE_10__* configuration_table ; 
 scalar_t__ finish_done ; 
 scalar_t__ finish_started ; 
 int /*<<< orphan*/  flush_pending (TYPE_1__*) ; 
 scalar_t__ need_more ; 
 int /*<<< orphan*/  putShortMSB (TYPE_2__*,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  zlib_tr_align (TYPE_2__*) ; 
 int /*<<< orphan*/  zlib_tr_stored_block (TYPE_2__*,char*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_tr_stored_type_only (TYPE_2__*) ; 

int zlib_deflate(
	z_streamp strm,
	int flush
)
{
    int old_flush; /* value of flush param for previous deflate call */
    deflate_state *s;

    if (strm == NULL || strm->state == NULL ||
	flush > Z_FINISH || flush < 0) {
        return Z_STREAM_ERROR;
    }
    s = (deflate_state *) strm->state;

    if ((strm->next_in == NULL && strm->avail_in != 0) ||
	(s->status == FINISH_STATE && flush != Z_FINISH)) {
        return Z_STREAM_ERROR;
    }
    if (strm->avail_out == 0) return Z_BUF_ERROR;

    s->strm = strm; /* just in case */
    old_flush = s->last_flush;
    s->last_flush = flush;

    /* Write the zlib header */
    if (s->status == INIT_STATE) {

        uInt header = (Z_DEFLATED + ((s->w_bits-8)<<4)) << 8;
        uInt level_flags = (s->level-1) >> 1;

        if (level_flags > 3) level_flags = 3;
        header |= (level_flags << 6);
	if (s->strstart != 0) header |= PRESET_DICT;
        header += 31 - (header % 31);

        s->status = BUSY_STATE;
        putShortMSB(s, header);

	/* Save the adler32 of the preset dictionary: */
	if (s->strstart != 0) {
	    putShortMSB(s, (uInt)(strm->adler >> 16));
	    putShortMSB(s, (uInt)(strm->adler & 0xffff));
	}
	strm->adler = 1L;
    }

    /* Flush as much pending output as possible */
    if (s->pending != 0) {
        flush_pending(strm);
        if (strm->avail_out == 0) {
	    /* Since avail_out is 0, deflate will be called again with
	     * more output space, but possibly with both pending and
	     * avail_in equal to zero. There won't be anything to do,
	     * but this is not an error situation so make sure we
	     * return OK instead of BUF_ERROR at next call of deflate:
             */
	    s->last_flush = -1;
	    return Z_OK;
	}

    /* Make sure there is something to do and avoid duplicate consecutive
     * flushes. For repeated and useless calls with Z_FINISH, we keep
     * returning Z_STREAM_END instead of Z_BUFF_ERROR.
     */
    } else if (strm->avail_in == 0 && flush <= old_flush &&
	       flush != Z_FINISH) {
        return Z_BUF_ERROR;
    }

    /* User must not provide more input after the first FINISH: */
    if (s->status == FINISH_STATE && strm->avail_in != 0) {
        return Z_BUF_ERROR;
    }

    /* Start a new block or continue the current one.
     */
    if (strm->avail_in != 0 || s->lookahead != 0 ||
        (flush != Z_NO_FLUSH && s->status != FINISH_STATE)) {
        block_state bstate;

	bstate = (*(configuration_table[s->level].func))(s, flush);

        if (bstate == finish_started || bstate == finish_done) {
            s->status = FINISH_STATE;
        }
        if (bstate == need_more || bstate == finish_started) {
	    if (strm->avail_out == 0) {
	        s->last_flush = -1; /* avoid BUF_ERROR next call, see above */
	    }
	    return Z_OK;
	    /* If flush != Z_NO_FLUSH && avail_out == 0, the next call
	     * of deflate should use the same flush parameter to make sure
	     * that the flush is complete. So we don't have to output an
	     * empty block here, this will be done at next call. This also
	     * ensures that for a very small output buffer, we emit at most
	     * one empty block.
	     */
	}
        if (bstate == block_done) {
            if (flush == Z_PARTIAL_FLUSH) {
                zlib_tr_align(s);
	    } else if (flush == Z_PACKET_FLUSH) {
		/* Output just the 3-bit `stored' block type value,
		   but not a zero length. */
		zlib_tr_stored_type_only(s);
            } else { /* FULL_FLUSH or SYNC_FLUSH */
                zlib_tr_stored_block(s, (char*)0, 0L, 0);
                /* For a full flush, this empty block will be recognized
                 * as a special marker by inflate_sync().
                 */
                if (flush == Z_FULL_FLUSH) {
                    CLEAR_HASH(s);             /* forget history */
                }
            }
            flush_pending(strm);
	    if (strm->avail_out == 0) {
	      s->last_flush = -1; /* avoid BUF_ERROR at next call, see above */
	      return Z_OK;
	    }
        }
    }
    Assert(strm->avail_out > 0, "bug2");

    if (flush != Z_FINISH) return Z_OK;
    if (s->noheader) return Z_STREAM_END;

    /* Write the zlib trailer (adler32) */
    putShortMSB(s, (uInt)(strm->adler >> 16));
    putShortMSB(s, (uInt)(strm->adler & 0xffff));
    flush_pending(strm);
    /* If avail_out is zero, the application will call deflate again
     * to flush the rest.
     */
    s->noheader = -1; /* write the trailer only once! */
    return s->pending != 0 ? Z_OK : Z_STREAM_END;
}