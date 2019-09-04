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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  gb; TYPE_1__** j_ac_vlc; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ IntraX8Context ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VLC_BITS ; 
 int /*<<< orphan*/  AC_VLC_MTD ; 
 int* ac_decode_table ; 
 int get_bits (int /*<<< orphan*/ ,int) ; 
 int get_bits1 (int /*<<< orphan*/ ) ; 
 int get_vlc2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x8_get_ac_rlf(IntraX8Context *const w, const int mode,
                          int *const run, int *const level, int *const final)
{
    int i, e;

//    x8_select_ac_table(w, mode);
    i = get_vlc2(w->gb, w->j_ac_vlc[mode]->table, AC_VLC_BITS, AC_VLC_MTD);

    if (i < 46) { // [0-45]
        int t, l;
        if (i < 0) {
            *level =
            *final =      // prevent 'may be used uninitialized'
            *run   = 64;  // this would cause error exit in the ac loop
            return;
        }

        /*
         * i == 0-15  r = 0-15 l = 0; r = i & %01111
         * i == 16-19 r = 0-3  l = 1; r = i & %00011
         * i == 20-21 r = 0-1  l = 2; r = i & %00001
         * i == 22    r = 0    l = 3; r = i & %00000
         */

        *final =
        t      = i > 22;
        i     -= 23 * t;

        /* l = lut_l[i / 2] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3 }[i >> 1];
         *     11 10'01 01'00 00'00 00'00 00'00 00 => 0xE50000 */
        l = (0xE50000 >> (i & 0x1E)) & 3; // 0x1E or ~1 or (i >> 1 << 1)

        /* t = lut_mask[l] = { 0x0f, 0x03, 0x01, 0x00 }[l];
         *     as i < 256 the higher bits do not matter */
        t = 0x01030F >> (l << 3);

        *run   = i & t;
        *level = l;
    } else if (i < 73) { // [46-72]
        uint32_t sm;
        uint32_t mask;

        i -= 46;
        sm = ac_decode_table[i];

        e    = get_bits(w->gb, sm & 0xF);
        sm >>= 8;                               // 3 bits
        mask = sm & 0xff;
        sm >>= 8;                               // 1 bit

        *run   = (sm &  0xff) + (e &  mask);    // 6 bits
        *level = (sm >>    8) + (e & ~mask);    // 5 bits
        *final = i > (58 - 46);
    } else if (i < 75) { // [73-74]
        static const uint8_t crazy_mix_runlevel[32] = {
            0x22, 0x32, 0x33, 0x53, 0x23, 0x42, 0x43, 0x63,
            0x24, 0x52, 0x34, 0x73, 0x25, 0x62, 0x44, 0x83,
            0x26, 0x72, 0x35, 0x54, 0x27, 0x82, 0x45, 0x64,
            0x28, 0x92, 0x36, 0x74, 0x29, 0xa2, 0x46, 0x84,
        };

        *final = !(i & 1);
        e      = get_bits(w->gb, 5); // get the extra bits
        *run   = crazy_mix_runlevel[e] >> 4;
        *level = crazy_mix_runlevel[e] & 0x0F;
    } else {
        *level = get_bits(w->gb, 7 - 3 * (i & 1));
        *run   = get_bits(w->gb, 6);
        *final = get_bits1(w->gb);
    }
    return;
}