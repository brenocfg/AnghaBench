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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_PVQ_V (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float celt_cwrsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int*) ; 
 int /*<<< orphan*/  ff_opus_rc_dec_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline float celt_decode_pulses(OpusRangeCoder *rc, int *y, uint32_t N, uint32_t K)
{
    const uint32_t idx = ff_opus_rc_dec_uint(rc, CELT_PVQ_V(N, K));
    return celt_cwrsi(N, K, idx, y);
}