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
typedef  scalar_t__ UINTFLOAT ;
typedef  int /*<<< orphan*/  INTFLOAT ;

/* Variables and functions */
 scalar_t__ AAC_MADD28 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void ps_add_squares_c(INTFLOAT *dst, const INTFLOAT (*src)[2], int n)
{
    int i;
    for (i = 0; i < n; i++)
        dst[i] += (UINTFLOAT)AAC_MADD28(src[i][0], src[i][0], src[i][1], src[i][1]);
}