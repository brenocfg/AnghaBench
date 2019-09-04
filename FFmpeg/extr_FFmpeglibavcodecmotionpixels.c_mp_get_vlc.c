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
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_7__ {int codes_count; TYPE_2__* codes; int /*<<< orphan*/  max_codes_bits; TYPE_1__ vlc; } ;
struct TYPE_6__ {int delta; } ;
typedef  TYPE_3__ MotionPixelsContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mp_get_vlc(MotionPixelsContext *mp, GetBitContext *gb)
{
    int i;

    i = (mp->codes_count == 1) ? 0 : get_vlc2(gb, mp->vlc.table, mp->max_codes_bits, 1);
    return mp->codes[i].delta;
}