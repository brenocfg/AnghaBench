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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RN64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WN64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get(uint8_t *pixels, int stride, int16_t* block)
{
    int i;

    for (i = 0; i < 8; i++) {
        AV_WN64(block, AV_RN64(pixels));
        AV_WN64(block+4, AV_RN64(pixels+8));
        pixels += stride;
        block += 8;
    }
}