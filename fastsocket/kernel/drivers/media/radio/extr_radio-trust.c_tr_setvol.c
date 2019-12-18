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
struct trust {int curvol; int /*<<< orphan*/  lock; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  TDA7318_ADDR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_i2c (struct trust*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tr_setvol(struct trust *tr, __u16 vol)
{
	mutex_lock(&tr->lock);
	tr->curvol = vol / 2048;
	write_i2c(tr, 2, TDA7318_ADDR, tr->curvol ^ 0x1f);
	mutex_unlock(&tr->lock);
}