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
typedef  scalar_t__ ush ;
typedef  long ulg ;
typedef  scalar_t__ uch ;
struct TYPE_8__ {size_t last_lit; int matches; int level; int lit_bufsize; TYPE_2__* dyn_dtree; scalar_t__ block_start; scalar_t__ strstart; TYPE_1__* dyn_ltree; scalar_t__* l_buf; scalar_t__* d_buf; } ;
typedef  TYPE_3__ deflate_state ;
struct TYPE_7__ {scalar_t__ Freq; } ;
struct TYPE_6__ {int /*<<< orphan*/  Freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int,char*) ; 
 int D_CODES ; 
 int LITERALS ; 
 scalar_t__ MAX_DIST (TYPE_3__*) ; 
 scalar_t__ MAX_MATCH ; 
 scalar_t__ MIN_MATCH ; 
 int /*<<< orphan*/  Tracev (int /*<<< orphan*/ ) ; 
 size_t d_code (unsigned int) ; 
 long* extra_dbits ; 
 int* length_code ; 
 int /*<<< orphan*/  stderr ; 

int zlib_tr_tally(
	deflate_state *s,
	unsigned dist,  /* distance of matched string */
	unsigned lc     /* match length-MIN_MATCH or unmatched char (if dist==0) */
)
{
    s->d_buf[s->last_lit] = (ush)dist;
    s->l_buf[s->last_lit++] = (uch)lc;
    if (dist == 0) {
        /* lc is the unmatched char */
        s->dyn_ltree[lc].Freq++;
    } else {
        s->matches++;
        /* Here, lc is the match length - MIN_MATCH */
        dist--;             /* dist = match distance - 1 */
        Assert((ush)dist < (ush)MAX_DIST(s) &&
               (ush)lc <= (ush)(MAX_MATCH-MIN_MATCH) &&
               (ush)d_code(dist) < (ush)D_CODES,  "zlib_tr_tally: bad match");

        s->dyn_ltree[length_code[lc]+LITERALS+1].Freq++;
        s->dyn_dtree[d_code(dist)].Freq++;
    }

    /* Try to guess if it is profitable to stop the current block here */
    if ((s->last_lit & 0xfff) == 0 && s->level > 2) {
        /* Compute an upper bound for the compressed length */
        ulg out_length = (ulg)s->last_lit*8L;
        ulg in_length = (ulg)((long)s->strstart - s->block_start);
        int dcode;
        for (dcode = 0; dcode < D_CODES; dcode++) {
            out_length += (ulg)s->dyn_dtree[dcode].Freq *
                (5L+extra_dbits[dcode]);
        }
        out_length >>= 3;
        Tracev((stderr,"\nlast_lit %u, in %ld, out ~%ld(%ld%%) ",
               s->last_lit, in_length, out_length,
               100L - out_length*100L/in_length));
        if (s->matches < s->last_lit/2 && out_length < in_length/2) return 1;
    }
    return (s->last_lit == s->lit_bufsize-1);
    /* We avoid equality with lit_bufsize because of wraparound at 64K
     * on 16 bit machines and because stored blocks are restricted to
     * 64K-1 bytes.
     */
}