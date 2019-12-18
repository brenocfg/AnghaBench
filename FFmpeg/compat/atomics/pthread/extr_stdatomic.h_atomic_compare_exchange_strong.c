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
 int /*<<< orphan*/  avpriv_atomic_lock () ; 
 int /*<<< orphan*/  avpriv_atomic_unlock () ; 

__attribute__((used)) static inline int atomic_compare_exchange_strong(intptr_t *object, intptr_t *expected,
                                                 intptr_t desired)
{
    int ret;
    avpriv_atomic_lock();
    if (*object == *expected) {
        ret     = 1;
        *object = desired;
    } else {
        ret = 0;
        *expected = *object;
    }
    avpriv_atomic_unlock();
    return ret;
}