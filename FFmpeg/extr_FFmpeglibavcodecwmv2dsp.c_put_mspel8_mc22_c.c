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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  wmv2_mspel8_h_lowpass (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmv2_mspel8_v_lowpass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void put_mspel8_mc22_c(uint8_t *dst, const uint8_t *src, ptrdiff_t stride)
{
    uint8_t halfH[88];

    wmv2_mspel8_h_lowpass(halfH, src - stride, 8, stride, 11);
    wmv2_mspel8_v_lowpass(dst, halfH + 8, stride, 8, 8);
}