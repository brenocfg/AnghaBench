#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* imdct_half ) (int /*<<< orphan*/ *,int*,int*) ;} ;
struct TYPE_12__ {int* buf_mdct; TYPE_2__* fdsp; int /*<<< orphan*/  mdct_ld; TYPE_1__ mdct; } ;
struct TYPE_11__ {scalar_t__* use_kb_window; } ;
struct TYPE_10__ {int* coeffs; int* ret; int* saved; TYPE_4__ ics; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* vector_fmul_window ) (int*,int*,int*,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_3__ SingleChannelElement ;
typedef  TYPE_4__ IndividualChannelStream ;
typedef  int INTFLOAT ;
typedef  TYPE_5__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_RENAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_sine_128 ; 
 int /*<<< orphan*/  ff_sine_512 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int*,int*,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void imdct_and_windowing_ld(AACContext *ac, SingleChannelElement *sce)
{
    IndividualChannelStream *ics = &sce->ics;
    INTFLOAT *in    = sce->coeffs;
    INTFLOAT *out   = sce->ret;
    INTFLOAT *saved = sce->saved;
    INTFLOAT *buf  = ac->buf_mdct;
#if USE_FIXED
    int i;
#endif /* USE_FIXED */

    // imdct
    ac->mdct.imdct_half(&ac->mdct_ld, buf, in);

#if USE_FIXED
    for (i = 0; i < 1024; i++)
        buf[i] = (buf[i] + 2) >> 2;
#endif /* USE_FIXED */

    // window overlapping
    if (ics->use_kb_window[1]) {
        // AAC LD uses a low overlap sine window instead of a KBD window
        memcpy(out, saved, 192 * sizeof(*out));
        ac->fdsp->vector_fmul_window(out + 192, saved + 192, buf, AAC_RENAME(ff_sine_128), 64);
        memcpy(                     out + 320, buf + 64, 192 * sizeof(*out));
    } else {
        ac->fdsp->vector_fmul_window(out, saved, buf, AAC_RENAME(ff_sine_512), 256);
    }

    // buffer update
    memcpy(saved, buf + 256, 256 * sizeof(*saved));
}