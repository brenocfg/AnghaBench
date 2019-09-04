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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FFABS (int /*<<< orphan*/ ) ; 
 int FFSIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT16_MAX ; 
 int cbrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_cbrt_h(int16_t sample, int height)
{
    return height/2 - FFSIGN(sample) * (cbrt(FFABS(sample)) * (height/2) / cbrt(INT16_MAX));
}