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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {void** u32; int /*<<< orphan*/  u8x4; } ;
typedef  TYPE_1__ av_aes_block ;

/* Variables and functions */
 void* mix_core (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** src ; 
 int /*<<< orphan*/ * uint8_t (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mix(av_aes_block state[2], uint32_t multbl[][256], int s1, int s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}