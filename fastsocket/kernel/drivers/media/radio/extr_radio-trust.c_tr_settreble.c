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
struct trust {int curtreble; int /*<<< orphan*/  lock; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  TDA7318_ADDR ; 
 int* basstreble2chip ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_i2c (struct trust*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tr_settreble(struct trust *tr, __u16 treble)
{
	mutex_lock(&tr->lock);
	tr->curtreble = treble / 4370;
	write_i2c(tr, 2, TDA7318_ADDR, 0x70 | basstreble2chip[tr->curtreble]);
	mutex_unlock(&tr->lock);
}