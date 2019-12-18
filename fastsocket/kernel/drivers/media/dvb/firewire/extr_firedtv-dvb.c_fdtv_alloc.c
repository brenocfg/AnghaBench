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
struct firedtv_backend {int dummy; } ;
struct firedtv {int isochannel; int voltage; int tone; int type; int /*<<< orphan*/  remote_ctrl_work; int /*<<< orphan*/  demux_mutex; int /*<<< orphan*/  avc_wait; int /*<<< orphan*/  avc_mutex; struct firedtv_backend const* backend; struct device* device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avc_remote_ctrl_work ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct firedtv*) ; 
 int /*<<< orphan*/ * fdtv_model_names ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct firedtv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

struct firedtv *fdtv_alloc(struct device *dev,
			   const struct firedtv_backend *backend,
			   const char *name, size_t name_len)
{
	struct firedtv *fdtv;
	int i;

	fdtv = kzalloc(sizeof(*fdtv), GFP_KERNEL);
	if (!fdtv)
		return NULL;

	dev_set_drvdata(dev, fdtv);
	fdtv->device		= dev;
	fdtv->isochannel	= -1;
	fdtv->voltage		= 0xff;
	fdtv->tone		= 0xff;
	fdtv->backend		= backend;

	mutex_init(&fdtv->avc_mutex);
	init_waitqueue_head(&fdtv->avc_wait);
	mutex_init(&fdtv->demux_mutex);
	INIT_WORK(&fdtv->remote_ctrl_work, avc_remote_ctrl_work);

	for (i = ARRAY_SIZE(fdtv_model_names); --i; )
		if (strlen(fdtv_model_names[i]) <= name_len &&
		    strncmp(name, fdtv_model_names[i], name_len) == 0)
			break;
	fdtv->type = i;

	return fdtv;
}