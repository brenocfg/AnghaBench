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
typedef  TYPE_1__* z_streamp ;
typedef  int /*<<< orphan*/  ush ;
typedef  int ulg ;
typedef  int /*<<< orphan*/  uch ;
struct internal_state {int dummy; } ;
struct TYPE_7__ {scalar_t__ overlay_memory; scalar_t__ head_memory; scalar_t__ prev_memory; scalar_t__ window_memory; int /*<<< orphan*/  deflate_memory; } ;
typedef  TYPE_2__ deflate_workspace ;
struct TYPE_8__ {int noheader; int w_bits; int w_size; int w_mask; int hash_bits; int hash_size; int hash_mask; int hash_shift; int lit_bufsize; int pending_buf_size; int level; int strategy; scalar_t__ method; int /*<<< orphan*/ * pending_buf; int /*<<< orphan*/ * l_buf; int /*<<< orphan*/ * d_buf; int /*<<< orphan*/ * head; int /*<<< orphan*/ * prev; scalar_t__* window; TYPE_1__* strm; } ;
typedef  TYPE_3__ deflate_state ;
struct TYPE_6__ {struct internal_state* state; scalar_t__ workspace; int /*<<< orphan*/ * msg; } ;
typedef  int /*<<< orphan*/  Pos ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int MAX_MEM_LEVEL ; 
 int MIN_MATCH ; 
 int Z_DEFAULT_COMPRESSION ; 
 int Z_DEFLATED ; 
 int Z_HUFFMAN_ONLY ; 
 int Z_STREAM_ERROR ; 
 int zlib_deflateReset (TYPE_1__*) ; 

int zlib_deflateInit2(
	z_streamp strm,
	int  level,
	int  method,
	int  windowBits,
	int  memLevel,
	int  strategy
)
{
    deflate_state *s;
    int noheader = 0;
    deflate_workspace *mem;

    ush *overlay;
    /* We overlay pending_buf and d_buf+l_buf. This works since the average
     * output size for (length,distance) codes is <= 24 bits.
     */

    if (strm == NULL) return Z_STREAM_ERROR;

    strm->msg = NULL;

    if (level == Z_DEFAULT_COMPRESSION) level = 6;

    mem = (deflate_workspace *) strm->workspace;

    if (windowBits < 0) { /* undocumented feature: suppress zlib header */
        noheader = 1;
        windowBits = -windowBits;
    }
    if (memLevel < 1 || memLevel > MAX_MEM_LEVEL || method != Z_DEFLATED ||
        windowBits < 9 || windowBits > 15 || level < 0 || level > 9 ||
	strategy < 0 || strategy > Z_HUFFMAN_ONLY) {
        return Z_STREAM_ERROR;
    }
    s = (deflate_state *) &(mem->deflate_memory);
    strm->state = (struct internal_state *)s;
    s->strm = strm;

    s->noheader = noheader;
    s->w_bits = windowBits;
    s->w_size = 1 << s->w_bits;
    s->w_mask = s->w_size - 1;

    s->hash_bits = memLevel + 7;
    s->hash_size = 1 << s->hash_bits;
    s->hash_mask = s->hash_size - 1;
    s->hash_shift =  ((s->hash_bits+MIN_MATCH-1)/MIN_MATCH);

    s->window = (Byte *) mem->window_memory;
    s->prev   = (Pos *)  mem->prev_memory;
    s->head   = (Pos *)  mem->head_memory;

    s->lit_bufsize = 1 << (memLevel + 6); /* 16K elements by default */

    overlay = (ush *) mem->overlay_memory;
    s->pending_buf = (uch *) overlay;
    s->pending_buf_size = (ulg)s->lit_bufsize * (sizeof(ush)+2L);

    s->d_buf = overlay + s->lit_bufsize/sizeof(ush);
    s->l_buf = s->pending_buf + (1+sizeof(ush))*s->lit_bufsize;

    s->level = level;
    s->strategy = strategy;
    s->method = (Byte)method;

    return zlib_deflateReset(strm);
}