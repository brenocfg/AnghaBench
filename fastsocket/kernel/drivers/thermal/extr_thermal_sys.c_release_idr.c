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
struct mutex {int dummy; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (struct idr*,int) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 

__attribute__((used)) static void release_idr(struct idr *idr, struct mutex *lock, int id)
{
	if (lock)
		mutex_lock(lock);
	idr_remove(idr, id);
	if (lock)
		mutex_unlock(lock);
}