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
struct TYPE_6__ {int /*<<< orphan*/  (* diff_int16 ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* diff_bytes ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ;} ;
struct TYPE_7__ {int bps; scalar_t__ n; TYPE_2__ hencdsp; TYPE_1__ llvidencdsp; } ;
typedef  TYPE_3__ HYuvContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__,int) ; 

__attribute__((used)) static inline void diff_bytes(HYuvContext *s, uint8_t *dst,
                              const uint8_t *src0, const uint8_t *src1, int w)
{
    if (s->bps <= 8) {
        s->llvidencdsp.diff_bytes(dst, src0, src1, w);
    } else {
        s->hencdsp.diff_int16((uint16_t *)dst, (const uint16_t *)src0, (const uint16_t *)src1, s->n - 1, w);
    }
}