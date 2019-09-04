#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* add_median_pred ) (int*,int*,int*,int,int*,int*) ;int /*<<< orphan*/  (* add_left_pred ) (int*,int*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ llviddsp; } ;
typedef  TYPE_2__ LagarithContext ;

/* Variables and functions */
 int mid_pred (int,int,int) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int*,int,int*,int*) ; 

__attribute__((used)) static void lag_pred_line_yuy2(LagarithContext *l, uint8_t *buf,
                               int width, int stride, int line,
                               int is_luma)
{
    int L, TL;

    if (!line) {
        L= buf[0];
        if (is_luma)
            buf[0] = 0;
        l->llviddsp.add_left_pred(buf, buf, width, 0);
        if (is_luma)
            buf[0] = L;
        return;
    }
    if (line == 1) {
        const int HEAD = is_luma ? 4 : 2;
        int i;

        L  = buf[width - stride - 1];
        TL = buf[HEAD  - stride - 1];
        for (i = 0; i < HEAD; i++) {
            L += buf[i];
            buf[i] = L;
        }
        for (; i < width; i++) {
            L      = mid_pred(L & 0xFF, buf[i - stride], (L + buf[i - stride] - TL) & 0xFF) + buf[i];
            TL     = buf[i - stride];
            buf[i] = L;
        }
    } else {
        TL = buf[width - (2 * stride) - 1];
        L  = buf[width - stride - 1];
        l->llviddsp.add_median_pred(buf, buf - stride, buf, width, &L, &TL);
    }
}