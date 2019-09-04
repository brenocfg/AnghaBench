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

__attribute__((used)) static inline intptr_t atomic_exchange(intptr_t *object, intptr_t desired)
{
    intptr_t ret;
    avpriv_atomic_lock();
    ret     = *object;
    *object = desired;
    avpriv_atomic_unlock();
    return ret;
}