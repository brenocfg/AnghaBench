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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int wp_log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int log2s(int32_t value)
{
    return (value < 0) ? -wp_log2(-value) : wp_log2(value);
}