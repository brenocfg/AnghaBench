#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 TYPE_1__* image ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vme_user_release(struct inode *inode, struct file *file)
{
	unsigned int minor = MINOR(inode->i_rdev);

	down(&image[minor].sem);

	/* Decrement user count */
	image[minor].users--;

	up(&image[minor].sem);

	return 0;
}