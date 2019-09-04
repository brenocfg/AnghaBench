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
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FFABS (int) ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int** ilbc_gain ; 

__attribute__((used)) static int16_t gain_dequantization(int index, int max_in, int stage)
{
    int16_t scale = FFMAX(1638, FFABS(max_in));

    return ((scale * ilbc_gain[stage][index]) + 8192) >> 14;
}