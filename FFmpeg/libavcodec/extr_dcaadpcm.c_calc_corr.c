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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ MUL64 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline int64_t calc_corr(const int32_t *x, int len, int j, int k)
{
    int n;
    int64_t s = 0;
    for (n = 0; n < len; n++)
        s += MUL64(x[n-j], x[n-k]);
    return s;
}