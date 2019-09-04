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
typedef  int /*<<< orphan*/  rep_t ;
typedef  int /*<<< orphan*/  fp_t ;

/* Variables and functions */

__attribute__((used)) static __inline rep_t toRep(fp_t x) {
    const union { fp_t f; rep_t i; } rep = {.f = x};
    return rep.i;
}