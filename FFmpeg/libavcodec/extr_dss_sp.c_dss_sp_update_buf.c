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

__attribute__((used)) static void dss_sp_update_buf(int32_t *hist, int32_t *vector)
{
    int i;

    for (i = 114; i > 0; i--)
        vector[i + 72] = vector[i];

    for (i = 0; i < 72; i++)
        vector[72 - i] = hist[i];
}