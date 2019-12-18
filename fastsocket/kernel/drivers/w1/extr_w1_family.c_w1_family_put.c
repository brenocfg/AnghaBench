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
struct w1_family {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __w1_family_put (struct w1_family*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w1_flock ; 

void w1_family_put(struct w1_family *f)
{
	spin_lock(&w1_flock);
	__w1_family_put(f);
	spin_unlock(&w1_flock);
}