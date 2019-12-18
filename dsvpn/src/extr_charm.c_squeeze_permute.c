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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  endian_swap_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  permute (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void squeeze_permute(uint32_t st[12], unsigned char dst[16])
{
    endian_swap_rate(st);
    memcpy(dst, st, 16);
    endian_swap_rate(st);
    permute(st);
}