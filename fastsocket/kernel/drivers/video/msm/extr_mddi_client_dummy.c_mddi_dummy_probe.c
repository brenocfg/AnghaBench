#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct msm_mddi_client_data* platform_data; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct TYPE_7__ {TYPE_3__* platform_data; } ;
struct TYPE_9__ {char* name; TYPE_2__ dev; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/  fb_data; int /*<<< orphan*/  caps; int /*<<< orphan*/  unblank; int /*<<< orphan*/  blank; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; } ;
struct panel_info {TYPE_4__ pdev; TYPE_3__ panel_data; } ;
struct msm_mddi_client_data {int /*<<< orphan*/  private_client_data; int /*<<< orphan*/  fb_resource; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSMFB_CAP_PARTIAL_UPDATES ; 
 int /*<<< orphan*/  kfree (struct panel_info*) ; 
 struct panel_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddi_dummy_blank ; 
 int /*<<< orphan*/  mddi_dummy_resume ; 
 int /*<<< orphan*/  mddi_dummy_suspend ; 
 int /*<<< orphan*/  mddi_dummy_unblank ; 
 int /*<<< orphan*/  platform_device_add_resources (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int platform_device_register (TYPE_4__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_info*) ; 

__attribute__((used)) static int mddi_dummy_probe(struct platform_device *pdev)
{
	struct msm_mddi_client_data *client_data = pdev->dev.platform_data;
	struct panel_info *panel =
		kzalloc(sizeof(struct panel_info), GFP_KERNEL);
	int ret;
	if (!panel)
		return -ENOMEM;
	platform_set_drvdata(pdev, panel);
	panel->panel_data.suspend = mddi_dummy_suspend;
	panel->panel_data.resume = mddi_dummy_resume;
	panel->panel_data.blank = mddi_dummy_blank;
	panel->panel_data.unblank = mddi_dummy_unblank;
	panel->panel_data.caps = MSMFB_CAP_PARTIAL_UPDATES;
	panel->pdev.name = "msm_panel";
	panel->pdev.id = pdev->id;
	platform_device_add_resources(&panel->pdev,
				      client_data->fb_resource, 1);
	panel->panel_data.fb_data = client_data->private_client_data;
	panel->pdev.dev.platform_data = &panel->panel_data;
	ret = platform_device_register(&panel->pdev);
	if (ret) {
		kfree(panel);
		return ret;
	}
	return 0;
}