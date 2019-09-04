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
typedef  int uint32_t ;
typedef  size_t X ;
struct TYPE_3__ {int* MDS1; int* MDS2; int* MDS3; int* MDS4; } ;
typedef  TYPE_1__ AVTWOFISH ;

/* Variables and functions */

__attribute__((used)) static uint32_t MDS_mul(AVTWOFISH *cs, uint32_t X)
{
    return cs->MDS1[(X) & 0xff] ^ cs->MDS2[((X) >> 8) & 0xff] ^ cs->MDS3[((X) >> 16) & 0xff] ^ cs->MDS4[(X) >> 24];
}