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
struct videobuf_dvb_frontends {int /*<<< orphan*/  lock; int /*<<< orphan*/  felist; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct videobuf_dvb_frontend {int id; int /*<<< orphan*/  felist; TYPE_1__ dvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct videobuf_dvb_frontend* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct videobuf_dvb_frontend *videobuf_dvb_alloc_frontend(
	struct videobuf_dvb_frontends *f, int id)
{
	struct videobuf_dvb_frontend *fe;

	fe = kzalloc(sizeof(struct videobuf_dvb_frontend), GFP_KERNEL);
	if (fe == NULL)
		goto fail_alloc;

	fe->id = id;
	mutex_init(&fe->dvb.lock);

	mutex_lock(&f->lock);
	list_add_tail(&fe->felist, &f->felist);
	mutex_unlock(&f->lock);

fail_alloc:
	return fe;
}