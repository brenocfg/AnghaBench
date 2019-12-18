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
 int s_rangeblockcnt ; 

__attribute__((used)) static inline int rangeblock_idx_valid(int rangeblock_idx)
{
    return (rangeblock_idx >= 0 && rangeblock_idx < s_rangeblockcnt);
}