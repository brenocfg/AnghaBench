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
struct r10conf {struct r10conf* mirrors; int /*<<< orphan*/  tmppage; scalar_t__ r10bio_pool; int /*<<< orphan*/  plug; } ;
struct mddev {struct r10conf* private; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct r10conf*) ; 
 int /*<<< orphan*/  lower_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  md_unregister_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  plugger_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raise_barrier (struct r10conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stop(struct mddev *mddev)
{
	struct r10conf *conf = mddev->private;

	raise_barrier(conf, 0);
	lower_barrier(conf);

	md_unregister_thread(&mddev->thread);
	plugger_flush(&conf->plug);

	if (conf->r10bio_pool)
		mempool_destroy(conf->r10bio_pool);
	safe_put_page(conf->tmppage);
	kfree(conf->mirrors);
	kfree(conf);
	mddev->private = NULL;
	return 0;
}