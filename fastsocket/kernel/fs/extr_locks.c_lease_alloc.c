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
struct file_lock {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct file_lock* ERR_PTR (int) ; 
 int lease_init (struct file*,int,struct file_lock*) ; 
 struct file_lock* locks_alloc_lock () ; 
 int /*<<< orphan*/  locks_free_lock (struct file_lock*) ; 

__attribute__((used)) static struct file_lock *lease_alloc(struct file *filp, int type)
{
	struct file_lock *fl = locks_alloc_lock();
	int error = -ENOMEM;

	if (fl == NULL)
		return ERR_PTR(error);

	error = lease_init(filp, type, fl);
	if (error) {
		locks_free_lock(fl);
		return ERR_PTR(error);
	}
	return fl;
}