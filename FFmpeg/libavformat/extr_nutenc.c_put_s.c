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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int FFABS (scalar_t__) ; 
 int /*<<< orphan*/  ff_put_v (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void put_s(AVIOContext *bc, int64_t val)
{
    ff_put_v(bc, 2 * FFABS(val) - (val > 0));
}