#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_7__ {scalar_t__ noheader; int /*<<< orphan*/  last_flush; int /*<<< orphan*/  status; int /*<<< orphan*/  pending_buf; int /*<<< orphan*/  pending_out; scalar_t__ pending; } ;
typedef  TYPE_2__ deflate_state ;
struct TYPE_6__ {int adler; int /*<<< orphan*/ * state; int /*<<< orphan*/  data_type; int /*<<< orphan*/ * msg; scalar_t__ total_out; scalar_t__ total_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY_STATE ; 
 int /*<<< orphan*/  INIT_STATE ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 
 int /*<<< orphan*/  Z_UNKNOWN ; 
 int /*<<< orphan*/  lm_init (TYPE_2__*) ; 
 int /*<<< orphan*/  zlib_tr_init (TYPE_2__*) ; 

int zlib_deflateReset(
	z_streamp strm
)
{
    deflate_state *s;
    
    if (strm == NULL || strm->state == NULL)
        return Z_STREAM_ERROR;

    strm->total_in = strm->total_out = 0;
    strm->msg = NULL;
    strm->data_type = Z_UNKNOWN;

    s = (deflate_state *)strm->state;
    s->pending = 0;
    s->pending_out = s->pending_buf;

    if (s->noheader < 0) {
        s->noheader = 0; /* was set to -1 by deflate(..., Z_FINISH); */
    }
    s->status = s->noheader ? BUSY_STATE : INIT_STATE;
    strm->adler = 1;
    s->last_flush = Z_NO_FLUSH;

    zlib_tr_init(s);
    lm_init(s);

    return Z_OK;
}