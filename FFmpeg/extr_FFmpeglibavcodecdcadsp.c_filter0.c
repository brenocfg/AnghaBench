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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  SUINT32 ;

/* Variables and functions */
 scalar_t__ mul22 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter0(SUINT32 *dst, const int32_t *src, int32_t coeff, ptrdiff_t len)
{
    int i;

    for (i = 0; i < len; i++)
        dst[i] -= mul22(src[i], coeff);
}