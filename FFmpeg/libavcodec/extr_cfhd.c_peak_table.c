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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {scalar_t__ level; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ Peak ;

/* Variables and functions */
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_get_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void peak_table(int16_t *band, Peak *peak, int length)
{
    int i;
    for (i = 0; i < length; i++)
        if (abs(band[i]) > peak->level)
            band[i] = bytestream2_get_le16(&peak->base);
}