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
struct zd_ioreq32 {int dummy; } ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zd_iowrite32a_locked (struct zd_chip*,struct zd_ioreq32 const*,unsigned int) ; 

int zd_iowrite32a(struct zd_chip *chip, const struct zd_ioreq32 *ioreqs,
	          unsigned int count)
{
	int r;

	mutex_lock(&chip->mutex);
	r = zd_iowrite32a_locked(chip, ioreqs, count);
	mutex_unlock(&chip->mutex);
	return r;
}