#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_6__*,int*,int*,int) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* imdct_half ) (int /*<<< orphan*/ *,int*,int*) ;} ;
struct TYPE_13__ {int* buf_mdct; int /*<<< orphan*/  mdct_ld; TYPE_3__ mdct; TYPE_6__* mdct480; TYPE_2__* oc; } ;
struct TYPE_12__ {int* coeffs; int* ret; int* saved; } ;
struct TYPE_9__ {scalar_t__ frame_length_short; } ;
struct TYPE_10__ {TYPE_1__ m4ac; } ;
typedef  TYPE_4__ SingleChannelElement ;
typedef  int INTFLOAT ;
typedef  TYPE_5__ AACContext ;

/* Variables and functions */
 int AAC_MUL31 (int,int const) ; 
 int* AAC_RENAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_aac_eld_window_480 ; 
 int /*<<< orphan*/  ff_aac_eld_window_512 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int const) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int*,int*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static void imdct_and_windowing_eld(AACContext *ac, SingleChannelElement *sce)
{
    INTFLOAT *in    = sce->coeffs;
    INTFLOAT *out   = sce->ret;
    INTFLOAT *saved = sce->saved;
    INTFLOAT *buf  = ac->buf_mdct;
    int i;
    const int n  = ac->oc[1].m4ac.frame_length_short ? 480 : 512;
    const int n2 = n >> 1;
    const int n4 = n >> 2;
    const INTFLOAT *const window = n == 480 ? AAC_RENAME(ff_aac_eld_window_480) :
                                           AAC_RENAME(ff_aac_eld_window_512);

    // Inverse transform, mapped to the conventional IMDCT by
    // Chivukula, R.K.; Reznik, Y.A.; Devarajan, V.,
    // "Efficient algorithms for MPEG-4 AAC-ELD, AAC-LD and AAC-LC filterbanks,"
    // International Conference on Audio, Language and Image Processing, ICALIP 2008.
    // URL: http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=4590245&isnumber=4589950
    for (i = 0; i < n2; i+=2) {
        INTFLOAT temp;
        temp =  in[i    ]; in[i    ] = -in[n - 1 - i]; in[n - 1 - i] = temp;
        temp = -in[i + 1]; in[i + 1] =  in[n - 2 - i]; in[n - 2 - i] = temp;
    }
#if !USE_FIXED
    if (n == 480)
        ac->mdct480->imdct_half(ac->mdct480, buf, in, 1);
    else
#endif
        ac->mdct.imdct_half(&ac->mdct_ld, buf, in);

#if USE_FIXED
    for (i = 0; i < 1024; i++)
      buf[i] = (buf[i] + 1) >> 1;
#endif /* USE_FIXED */

    for (i = 0; i < n; i+=2) {
        buf[i] = -buf[i];
    }
    // Like with the regular IMDCT at this point we still have the middle half
    // of a transform but with even symmetry on the left and odd symmetry on
    // the right

    // window overlapping
    // The spec says to use samples [0..511] but the reference decoder uses
    // samples [128..639].
    for (i = n4; i < n2; i ++) {
        out[i - n4] = AAC_MUL31(   buf[    n2 - 1 - i] , window[i       - n4]) +
                      AAC_MUL31( saved[        i + n2] , window[i +   n - n4]) +
                      AAC_MUL31(-saved[n + n2 - 1 - i] , window[i + 2*n - n4]) +
                      AAC_MUL31(-saved[  2*n + n2 + i] , window[i + 3*n - n4]);
    }
    for (i = 0; i < n2; i ++) {
        out[n4 + i] = AAC_MUL31(   buf[              i] , window[i + n2       - n4]) +
                      AAC_MUL31(-saved[      n - 1 - i] , window[i + n2 +   n - n4]) +
                      AAC_MUL31(-saved[          n + i] , window[i + n2 + 2*n - n4]) +
                      AAC_MUL31( saved[2*n + n - 1 - i] , window[i + n2 + 3*n - n4]);
    }
    for (i = 0; i < n4; i ++) {
        out[n2 + n4 + i] = AAC_MUL31(   buf[    i + n2] , window[i +   n - n4]) +
                           AAC_MUL31(-saved[n2 - 1 - i] , window[i + 2*n - n4]) +
                           AAC_MUL31(-saved[n + n2 + i] , window[i + 3*n - n4]);
    }

    // buffer update
    memmove(saved + n, saved, 2 * n * sizeof(*saved));
    memcpy( saved,       buf,     n * sizeof(*saved));
}