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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  abs (int /*<<< orphan*/ ) ; 
 scalar_t__ log2sample (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t log2mono(int32_t *samples, int nb_samples, int limit)
{
    uint32_t result = 0;
    while (nb_samples--) {
        if (log2sample(abs(*samples++), limit, &result))
            return UINT32_MAX;
    }
    return result;
}