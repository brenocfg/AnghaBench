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
struct r5conf {struct r5conf* stripe_hashtbl; struct r5conf* disks; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct r5conf*) ; 
 int /*<<< orphan*/  raid5_free_percpu (struct r5conf*) ; 
 int /*<<< orphan*/  shrink_stripes (struct r5conf*) ; 

__attribute__((used)) static void free_conf(struct r5conf *conf)
{
	shrink_stripes(conf);
	raid5_free_percpu(conf);
	kfree(conf->disks);
	kfree(conf->stripe_hashtbl);
	kfree(conf);
}