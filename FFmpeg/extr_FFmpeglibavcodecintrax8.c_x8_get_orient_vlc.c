#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int quant; TYPE_3__* j_orient_vlc; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ IntraX8Context ;

/* Variables and functions */
 int /*<<< orphan*/  OR_VLC_BITS ; 
 int /*<<< orphan*/  OR_VLC_MTD ; 
 int get_bits (int /*<<< orphan*/ ,int) ; 
 int get_vlc2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__** j_orient_vlc ; 

__attribute__((used)) static inline int x8_get_orient_vlc(IntraX8Context *w)
{
    if (!w->j_orient_vlc) {
        int table_index = get_bits(w->gb, 1 + (w->quant < 13));
        w->j_orient_vlc = &j_orient_vlc[w->quant < 13][table_index];
    }

    return get_vlc2(w->gb, w->j_orient_vlc->table, OR_VLC_BITS, OR_VLC_MTD);
}