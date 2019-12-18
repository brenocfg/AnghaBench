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
struct TYPE_3__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ VLC ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* vlc_stage3_values ; 

__attribute__((used)) static int qdm2_get_vlc(GetBitContext *gb, const VLC *vlc, int flag, int depth)
{
    int value;

    value = get_vlc2(gb, vlc->table, vlc->bits, depth);

    /* stage-2, 3 bits exponent escape sequence */
    if (value-- == 0)
        value = get_bits(gb, get_bits(gb, 3) + 1);

    /* stage-3, optional */
    if (flag) {
        int tmp;

        if (value >= 60) {
            av_log(NULL, AV_LOG_ERROR, "value %d in qdm2_get_vlc too large\n", value);
            return 0;
        }

        tmp= vlc_stage3_values[value];

        if ((value & ~3) > 0)
            tmp += get_bits(gb, (value >> 2));
        value = tmp;
    }

    return value;
}