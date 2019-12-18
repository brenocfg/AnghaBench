#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int len; int lit; int* p; } ;
typedef  TYPE_1__ HufDec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HUF_DECBITS ; 
 int* av_realloc (int*,int) ; 

__attribute__((used)) static int huf_build_dec_table(const uint64_t *hcode, int im,
                               int iM, HufDec *hdecod)
{
    for (; im <= iM; im++) {
        uint64_t c = hcode[im] >> 6;
        int i, l = hcode[im] & 63;

        if (c >> l)
            return AVERROR_INVALIDDATA;

        if (l > HUF_DECBITS) {
            HufDec *pl = hdecod + (c >> (l - HUF_DECBITS));
            if (pl->len)
                return AVERROR_INVALIDDATA;

            pl->lit++;

            pl->p = av_realloc(pl->p, pl->lit * sizeof(int));
            if (!pl->p)
                return AVERROR(ENOMEM);

            pl->p[pl->lit - 1] = im;
        } else if (l) {
            HufDec *pl = hdecod + (c << (HUF_DECBITS - l));

            for (i = 1 << (HUF_DECBITS - l); i > 0; i--, pl++) {
                if (pl->len || pl->p)
                    return AVERROR_INVALIDDATA;
                pl->len = l;
                pl->lit = im;
            }
        }
    }

    return 0;
}