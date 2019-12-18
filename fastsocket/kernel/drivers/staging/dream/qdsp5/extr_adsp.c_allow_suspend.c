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
 int /*<<< orphan*/  adsp_wake_lock ; 
 int /*<<< orphan*/  wake_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void allow_suspend(void)
{
	wake_unlock(&adsp_wake_lock);
}