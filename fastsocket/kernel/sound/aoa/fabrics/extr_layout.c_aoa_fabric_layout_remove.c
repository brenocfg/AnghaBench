#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct soundbus_dev {int pcmid; int /*<<< orphan*/ * pcmname; TYPE_1__ ofdev; } ;
struct TYPE_8__ {TYPE_2__* methods; } ;
struct layout_dev {TYPE_3__ gpio; int /*<<< orphan*/  sound; int /*<<< orphan*/  list; int /*<<< orphan*/ ** codecs; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* exit ) (TYPE_3__*) ;int /*<<< orphan*/  (* set_notify ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AOA_NOTIFY_HEADPHONE ; 
 int /*<<< orphan*/  AOA_NOTIFY_LINE_OUT ; 
 int MAX_CODECS_PER_BUS ; 
 int /*<<< orphan*/  aoa_fabric_unlink_codec (int /*<<< orphan*/ *) ; 
 struct layout_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct layout_dev*) ; 
 int /*<<< orphan*/ * layout_device ; 
 int /*<<< orphan*/  layouts_list_items ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 

__attribute__((used)) static int aoa_fabric_layout_remove(struct soundbus_dev *sdev)
{
	struct layout_dev *ldev = dev_get_drvdata(&sdev->ofdev.dev);
	int i;

	for (i=0; i<MAX_CODECS_PER_BUS; i++) {
		if (ldev->codecs[i]) {
			aoa_fabric_unlink_codec(ldev->codecs[i]);
		}
		ldev->codecs[i] = NULL;
	}
	list_del(&ldev->list);
	layouts_list_items--;
	of_node_put(ldev->sound);

	ldev->gpio.methods->set_notify(&ldev->gpio,
				       AOA_NOTIFY_HEADPHONE,
				       NULL,
				       NULL);
	ldev->gpio.methods->set_notify(&ldev->gpio,
				       AOA_NOTIFY_LINE_OUT,
				       NULL,
				       NULL);

	ldev->gpio.methods->exit(&ldev->gpio);
	layout_device = NULL;
	kfree(ldev);
	sdev->pcmid = -1;
	sdev->pcmname = NULL;
	return 0;
}