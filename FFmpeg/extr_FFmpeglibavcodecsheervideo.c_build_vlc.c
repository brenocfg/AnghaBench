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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  VLC ;

/* Variables and functions */
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 int ff_init_vlc_sparse (int /*<<< orphan*/ *,int,int,int*,int,int,int*,int,int,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_vlc(VLC *vlc, const uint8_t *len, int count)
{
    uint32_t codes[1024];
    uint8_t bits[1024];
    uint16_t syms[1024];
    uint64_t index;
    int i;

    index = 0;
    for (i = 0; i < count; i++) {
        codes[i]  = index >> (32 - len[i]);
        bits[i] = len[i];
        syms[i]  = i;
        index += 1ULL << (32 - len[i]);
    }

    ff_free_vlc(vlc);
    return ff_init_vlc_sparse(vlc, 16, count,
                              bits,  sizeof(*bits),  sizeof(*bits),
                              codes, sizeof(*codes), sizeof(*codes),
                              syms,  sizeof(*syms),  sizeof(*syms), 0);
}