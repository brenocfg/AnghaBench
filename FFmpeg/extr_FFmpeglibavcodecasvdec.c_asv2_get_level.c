#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  ASV2_LEVEL_VLC_BITS ; 
 int /*<<< orphan*/  asv2_get_bits (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ asv2_level_vlc ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int asv2_get_level(GetBitContext *gb)
{
    int code = get_vlc2(gb, asv2_level_vlc.table, ASV2_LEVEL_VLC_BITS, 1);

    if (code == 31)
        return (int8_t) asv2_get_bits(gb, 8);
    else
        return code - 31;
}