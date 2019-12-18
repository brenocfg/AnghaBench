#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* diff_int16 ) (int*,int const*,int const*,scalar_t__,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* diff_bytes ) (int*,int const*,int const*,int) ;} ;
struct TYPE_7__ {int bps; scalar_t__ n; TYPE_2__ hencdsp; TYPE_1__ llvidencdsp; } ;
typedef  TYPE_3__ HYuvContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  stub1 (int*,int const*,int const*,int) ; 
 int /*<<< orphan*/  stub2 (int*,int const*,int const*,scalar_t__,int) ; 

__attribute__((used)) static inline int sub_left_prediction(HYuvContext *s, uint8_t *dst,
                                      const uint8_t *src, int w, int left)
{
    int i;
    int min_width = FFMIN(w, 32);

    if (s->bps <= 8) {
        for (i = 0; i < min_width; i++) { /* scalar loop before dsp call */
            const int temp = src[i];
            dst[i] = temp - left;
            left   = temp;
        }
        if (w < 32)
            return left;
        s->llvidencdsp.diff_bytes(dst + 32, src + 32, src + 31, w - 32);
        return src[w-1];
    } else {
        const uint16_t *src16 = (const uint16_t *)src;
        uint16_t       *dst16 = (      uint16_t *)dst;
        for (i = 0; i < min_width; i++) { /* scalar loop before dsp call */
            const int temp = src16[i];
            dst16[i] = temp - left;
            left   = temp;
        }
        if (w < 32)
            return left;
        s->hencdsp.diff_int16(dst16 + 32, src16 + 32, src16 + 31, s->n - 1, w - 32);
        return src16[w-1];
    }
}