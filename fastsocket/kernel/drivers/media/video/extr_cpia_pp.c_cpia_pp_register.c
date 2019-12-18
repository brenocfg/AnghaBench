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
struct pp_cam_entry {scalar_t__ stream_irq; scalar_t__ streaming; int /*<<< orphan*/  wq_stream; struct parport* port; struct pardevice* pdev; } ;
struct parport {int modes; } ;
struct pardevice {int dummy; } ;
struct cam_data {int /*<<< orphan*/  cam_data_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int PARPORT_MODE_PCSPP ; 
 int /*<<< orphan*/  cam_list ; 
 int /*<<< orphan*/  cam_list_lock_pp ; 
 int /*<<< orphan*/  cpia_pp_ops ; 
 struct cam_data* cpia_register_camera (int /*<<< orphan*/ *,struct pp_cam_entry*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pp_cam_entry*) ; 
 struct pp_cam_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pardevice* parport_register_device (struct parport*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pp_cam_entry*) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpia_pp_register(struct parport *port)
{
	struct pardevice *pdev = NULL;
	struct pp_cam_entry *cam;
	struct cam_data *cpia;

	if (!(port->modes & PARPORT_MODE_PCSPP)) {
		LOG("port is not supported by CPiA driver\n");
		return -ENXIO;
	}

	cam = kzalloc(sizeof(struct pp_cam_entry), GFP_KERNEL);
	if (cam == NULL) {
		LOG("failed to allocate camera structure\n");
		return -ENOMEM;
	}

	pdev = parport_register_device(port, "cpia_pp", NULL, NULL,
				       NULL, 0, cam);

	if (!pdev) {
		LOG("failed to parport_register_device\n");
		kfree(cam);
		return -ENXIO;
	}

	cam->pdev = pdev;
	cam->port = port;
	init_waitqueue_head(&cam->wq_stream);

	cam->streaming = 0;
	cam->stream_irq = 0;

	if((cpia = cpia_register_camera(&cpia_pp_ops, cam)) == NULL) {
		LOG("failed to cpia_register_camera\n");
		parport_unregister_device(pdev);
		kfree(cam);
		return -ENXIO;
	}
	spin_lock( &cam_list_lock_pp );
	list_add( &cpia->cam_data_list, &cam_list );
	spin_unlock( &cam_list_lock_pp );

	return 0;
}