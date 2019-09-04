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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int (* add_left_pred ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ;int (* add_left_pred_int16 ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int,int) ;} ;
struct TYPE_5__ {int bps; scalar_t__ n; TYPE_1__ llviddsp; } ;
typedef  TYPE_2__ HYuvContext ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int,int) ; 

__attribute__((used)) static int left_prediction(HYuvContext *s, uint8_t *dst, const uint8_t *src, int w, int acc)
{
    if (s->bps <= 8) {
        return s->llviddsp.add_left_pred(dst, src, w, acc);
    } else {
        return s->llviddsp.add_left_pred_int16((      uint16_t *)dst, (const uint16_t *)src, s->n-1, w, acc);
    }
}