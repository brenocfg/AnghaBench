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
struct r5conf {int /*<<< orphan*/  active_stripes; } ;
struct mddev {struct r5conf* private; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
stripe_cache_active_show(struct mddev *mddev, char *page)
{
	struct r5conf *conf = mddev->private;
	if (conf)
		return sprintf(page, "%d\n", atomic_read(&conf->active_stripes));
	else
		return 0;
}