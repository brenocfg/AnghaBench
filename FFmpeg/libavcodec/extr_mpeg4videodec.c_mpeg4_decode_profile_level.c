#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mpeg4_decode_profile_level(MpegEncContext *s, GetBitContext *gb, int *profile, int *level)
{

    *profile = get_bits(gb, 4);
    *level   = get_bits(gb, 4);

    // for Simple profile, level 0
    if (*profile == 0 && *level == 8) {
        *level = 0;
    }

    return 0;
}