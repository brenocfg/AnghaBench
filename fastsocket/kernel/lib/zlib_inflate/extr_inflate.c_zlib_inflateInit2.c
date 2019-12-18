#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct internal_state {int dummy; } ;
struct inflate_state {int wrap; unsigned int wbits; int /*<<< orphan*/ * window; } ;
struct TYPE_7__ {int /*<<< orphan*/ * working_window; struct inflate_state inflate_state; } ;
struct TYPE_6__ {struct internal_state* state; int /*<<< orphan*/ * msg; } ;

/* Variables and functions */
 TYPE_4__* WS (TYPE_1__*) ; 
 int Z_STREAM_ERROR ; 
 int zlib_inflateReset (TYPE_1__*) ; 

int zlib_inflateInit2(z_streamp strm, int windowBits)
{
    struct inflate_state *state;

    if (strm == NULL) return Z_STREAM_ERROR;
    strm->msg = NULL;                 /* in case we return an error */

    state = &WS(strm)->inflate_state;
    strm->state = (struct internal_state *)state;

    if (windowBits < 0) {
        state->wrap = 0;
        windowBits = -windowBits;
    }
    else {
        state->wrap = (windowBits >> 4) + 1;
    }
    if (windowBits < 8 || windowBits > 15) {
        return Z_STREAM_ERROR;
    }
    state->wbits = (unsigned)windowBits;
    state->window = &WS(strm)->working_window[0];

    return zlib_inflateReset(strm);
}