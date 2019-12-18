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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* add_hfyu_median_pred_int16 ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int,int*,int*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* add_median_pred ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int*,int*) ;} ;
struct TYPE_7__ {int bps; scalar_t__ n; TYPE_2__ hdsp; TYPE_1__ llviddsp; } ;
typedef  TYPE_3__ HYuvContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int*,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int,int*,int*) ; 

__attribute__((used)) static void add_median_prediction(HYuvContext *s, uint8_t *dst, const uint8_t *src, const uint8_t *diff, int w, int *left, int *left_top)
{
    if (s->bps <= 8) {
        s->llviddsp.add_median_pred(dst, src, diff, w, left, left_top);
    } else {
        s->hdsp.add_hfyu_median_pred_int16((uint16_t *)dst, (const uint16_t *)src, (const uint16_t *)diff, s->n-1, w, left, left_top);
    }
}