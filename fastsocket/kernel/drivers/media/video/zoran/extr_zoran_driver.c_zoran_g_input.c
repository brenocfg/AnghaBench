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
struct zoran_fh {struct zoran* zr; } ;
struct zoran {unsigned int input; int /*<<< orphan*/  resource_lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zoran_g_input(struct file *file, void *__fh, unsigned int *input)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	mutex_lock(&zr->resource_lock);
	*input = zr->input;
	mutex_unlock(&zr->resource_lock);

	return 0;
}