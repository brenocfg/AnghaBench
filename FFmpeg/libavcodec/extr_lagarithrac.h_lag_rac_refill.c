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
struct TYPE_3__ {int range; int low; scalar_t__ bytestream; scalar_t__ bytestream_end; int /*<<< orphan*/  overread; } ;
typedef  TYPE_1__ lag_rac ;

/* Variables and functions */
 int AV_RB16 (scalar_t__) ; 

__attribute__((used)) static inline void lag_rac_refill(lag_rac *l)
{
    while (l->range <= 0x800000) {
        l->low   <<= 8;
        l->range <<= 8;
        l->low |= 0xff & (AV_RB16(l->bytestream) >> 1);
        if (l->bytestream < l->bytestream_end)
            l->bytestream++;
        else
            l->overread++;
    }
}