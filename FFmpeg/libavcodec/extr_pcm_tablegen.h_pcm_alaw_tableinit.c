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

/* Variables and functions */
 int /*<<< orphan*/  alaw2linear ; 
 int /*<<< orphan*/  build_xlaw_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  linear_to_alaw ; 

__attribute__((used)) static void pcm_alaw_tableinit(void)
{
    build_xlaw_table(linear_to_alaw, alaw2linear, 0xd5);
}