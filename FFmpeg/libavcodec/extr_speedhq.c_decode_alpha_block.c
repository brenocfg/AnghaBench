#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  SHQContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_VLC_BITS ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_VLC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_CACHE_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ ff_dc_alpha_level_vlc_le ; 
 TYPE_1__ ff_dc_alpha_run_vlc_le ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  re ; 

__attribute__((used)) static inline int decode_alpha_block(const SHQContext *s, GetBitContext *gb, uint8_t last_alpha[16], uint8_t *dest, int linesize)
{
    uint8_t block[128];
    int i = 0, x, y;

    memset(block, 0, sizeof(block));

    {
        OPEN_READER(re, gb);

        for ( ;; ) {
            int run, level;

            UPDATE_CACHE_LE(re, gb);
            GET_VLC(run, re, gb, ff_dc_alpha_run_vlc_le.table, ALPHA_VLC_BITS, 2);

            if (run < 0) break;
            i += run;
            if (i >= 128)
                return AVERROR_INVALIDDATA;

            UPDATE_CACHE_LE(re, gb);
            GET_VLC(level, re, gb, ff_dc_alpha_level_vlc_le.table, ALPHA_VLC_BITS, 2);
            block[i++] = level;
        }

        CLOSE_READER(re, gb);
    }

    for (y = 0; y < 8; y++) {
        for (x = 0; x < 16; x++) {
            last_alpha[x] -= block[y * 16 + x];
        }
        memcpy(dest, last_alpha, 16);
        dest += linesize;
    }

    return 0;
}