#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct claw_privbk {TYPE_1__* p_env; int /*<<< orphan*/ * p_mtc_envelope; } ;
struct claw_env {int dummy; } ;
struct ccwgroup_device {TYPE_2__** cdev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {void* handler; } ;
struct TYPE_3__ {int write_buffers; int read_buffers; struct claw_privbk* p_priv; void* write_size; void* read_size; scalar_t__ packing; int /*<<< orphan*/  api_type; int /*<<< orphan*/  host_name; int /*<<< orphan*/  adapter_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int) ; 
 void* CLAW_FRAME_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ENVELOPE_SIZE ; 
 int /*<<< orphan*/  WS_NAME_NOT_DEF ; 
 int claw_add_files (int /*<<< orphan*/ *) ; 
 void* claw_irq_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct claw_privbk*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  probe_error (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static int
claw_probe(struct ccwgroup_device *cgdev)
{
	int  		rc;
	struct claw_privbk *privptr=NULL;

	CLAW_DBF_TEXT(2, setup, "probe");
	if (!get_device(&cgdev->dev))
		return -ENODEV;
	privptr = kzalloc(sizeof(struct claw_privbk), GFP_KERNEL);
	dev_set_drvdata(&cgdev->dev, privptr);
	if (privptr == NULL) {
		probe_error(cgdev);
		put_device(&cgdev->dev);
		CLAW_DBF_TEXT_(2, setup, "probex%d", -ENOMEM);
		return -ENOMEM;
	}
	privptr->p_mtc_envelope= kzalloc( MAX_ENVELOPE_SIZE, GFP_KERNEL);
	privptr->p_env = kzalloc(sizeof(struct claw_env), GFP_KERNEL);
        if ((privptr->p_mtc_envelope==NULL) || (privptr->p_env==NULL)) {
                probe_error(cgdev);
		put_device(&cgdev->dev);
		CLAW_DBF_TEXT_(2, setup, "probex%d", -ENOMEM);
                return -ENOMEM;
        }
	memcpy(privptr->p_env->adapter_name,WS_NAME_NOT_DEF,8);
	memcpy(privptr->p_env->host_name,WS_NAME_NOT_DEF,8);
	memcpy(privptr->p_env->api_type,WS_NAME_NOT_DEF,8);
	privptr->p_env->packing = 0;
	privptr->p_env->write_buffers = 5;
	privptr->p_env->read_buffers = 5;
	privptr->p_env->read_size = CLAW_FRAME_SIZE;
	privptr->p_env->write_size = CLAW_FRAME_SIZE;
	rc = claw_add_files(&cgdev->dev);
	if (rc) {
		probe_error(cgdev);
		put_device(&cgdev->dev);
		dev_err(&cgdev->dev, "Creating the /proc files for a new"
		" CLAW device failed\n");
		CLAW_DBF_TEXT_(2, setup, "probex%d", rc);
		return rc;
	}
	privptr->p_env->p_priv = privptr;
        cgdev->cdev[0]->handler = claw_irq_handler;
	cgdev->cdev[1]->handler = claw_irq_handler;
	CLAW_DBF_TEXT(2, setup, "prbext 0");

        return 0;
}