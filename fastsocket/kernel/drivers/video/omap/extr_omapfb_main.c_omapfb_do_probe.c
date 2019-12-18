#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * platform_data; } ;
struct platform_device {scalar_t__ num_resources; TYPE_5__ dev; } ;
struct TYPE_8__ {int region_cnt; TYPE_2__* region; } ;
struct omapfb_device {TYPE_3__ mem_desc; struct lcd_panel* panel; int /*<<< orphan*/  state; TYPE_5__* dev; int /*<<< orphan*/ * fb_info; TYPE_1__* ctrl; int /*<<< orphan*/ * ext_if; int /*<<< orphan*/ * int_ctrl; int /*<<< orphan*/  rqueue_mutex; } ;
struct lcd_panel {int (* init ) (struct lcd_panel*,struct omapfb_device*) ;unsigned long x_res; unsigned long y_res; int (* enable ) (struct lcd_panel*) ;int pixel_clock; unsigned long hfp; unsigned long hbp; unsigned long hsw; unsigned long vfp; unsigned long vbp; unsigned long vsw; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  fb_mmap; } ;
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_6__ {int (* enable_plane ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/ * mmap; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMAPFB_ACTIVE ; 
 int /*<<< orphan*/  OMAPFB_AUTO_UPDATE ; 
 int /*<<< orphan*/  OMAPFB_MANUAL_UPDATE ; 
 int /*<<< orphan*/  OMAPFB_PLANE_GFX ; 
 int /*<<< orphan*/  OMAP_DMA_PORT_EMIFF ; 
 int /*<<< orphan*/  check_required_callbacks (struct omapfb_device*) ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 int ctrl_change_mode (int /*<<< orphan*/ ) ; 
 int ctrl_init (struct omapfb_device*) ; 
 unsigned long def_vxres ; 
 unsigned long def_vyres ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 struct omapfb_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ manual_update ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap1_ext_if ; 
 int /*<<< orphan*/  omap1_int_ctrl ; 
 int /*<<< orphan*/  omap2_ext_if ; 
 int /*<<< orphan*/  omap2_int_ctrl ; 
 int /*<<< orphan*/  omap_set_dma_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct omapfb_device* omapfb_dev ; 
 scalar_t__ omapfb_find_ctrl (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_free_resources (struct omapfb_device*,int) ; 
 int /*<<< orphan*/  omapfb_mmap ; 
 TYPE_4__ omapfb_ops ; 
 int omapfb_register_sysfs (struct omapfb_device*) ; 
 int /*<<< orphan*/  omapfb_set_update_mode (struct omapfb_device*,int /*<<< orphan*/ ) ; 
 int planes_init (struct omapfb_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omapfb_device*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,...) ; 
 int register_framebuffer (int /*<<< orphan*/ ) ; 
 int stub1 (struct lcd_panel*,struct omapfb_device*) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 
 int stub3 (struct lcd_panel*) ; 

__attribute__((used)) static int omapfb_do_probe(struct platform_device *pdev,
				struct lcd_panel *panel)
{
	struct omapfb_device	*fbdev = NULL;
	int			init_state;
	unsigned long		phz, hhz, vhz;
	unsigned long		vram;
	int			i;
	int			r = 0;

	init_state = 0;

	if (pdev->num_resources != 0) {
		dev_err(&pdev->dev, "probed for an unknown device\n");
		r = -ENODEV;
		goto cleanup;
	}

	if (pdev->dev.platform_data == NULL) {
		dev_err(&pdev->dev, "missing platform data\n");
		r = -ENOENT;
		goto cleanup;
	}

	fbdev = kzalloc(sizeof(struct omapfb_device), GFP_KERNEL);
	if (fbdev == NULL) {
		dev_err(&pdev->dev,
			"unable to allocate memory for device info\n");
		r = -ENOMEM;
		goto cleanup;
	}
	init_state++;

	fbdev->dev = &pdev->dev;
	fbdev->panel = panel;
	platform_set_drvdata(pdev, fbdev);

	mutex_init(&fbdev->rqueue_mutex);

#ifdef CONFIG_ARCH_OMAP1
	fbdev->int_ctrl = &omap1_int_ctrl;
#ifdef CONFIG_FB_OMAP_LCDC_EXTERNAL
	fbdev->ext_if = &omap1_ext_if;
#endif
#else	/* OMAP2 */
	fbdev->int_ctrl = &omap2_int_ctrl;
#ifdef CONFIG_FB_OMAP_LCDC_EXTERNAL
	fbdev->ext_if = &omap2_ext_if;
#endif
#endif
	if (omapfb_find_ctrl(fbdev) < 0) {
		dev_err(fbdev->dev,
			"LCD controller not found, board not supported\n");
		r = -ENODEV;
		goto cleanup;
	}

	r = fbdev->panel->init(fbdev->panel, fbdev);
	if (r)
		goto cleanup;

	pr_info("omapfb: configured for panel %s\n", fbdev->panel->name);

	def_vxres = def_vxres ? def_vxres : fbdev->panel->x_res;
	def_vyres = def_vyres ? def_vyres : fbdev->panel->y_res;

	init_state++;

	r = ctrl_init(fbdev);
	if (r)
		goto cleanup;
	if (fbdev->ctrl->mmap != NULL)
		omapfb_ops.fb_mmap = omapfb_mmap;
	init_state++;

	check_required_callbacks(fbdev);

	r = planes_init(fbdev);
	if (r)
		goto cleanup;
	init_state++;

#ifdef CONFIG_FB_OMAP_DMA_TUNE
	/* Set DMA priority for EMIFF access to highest */
	if (cpu_class_is_omap1())
		omap_set_dma_priority(0, OMAP_DMA_PORT_EMIFF, 15);
#endif

	r = ctrl_change_mode(fbdev->fb_info[0]);
	if (r) {
		dev_err(fbdev->dev, "mode setting failed\n");
		goto cleanup;
	}

	/* GFX plane is enabled by default */
	r = fbdev->ctrl->enable_plane(OMAPFB_PLANE_GFX, 1);
	if (r)
		goto cleanup;

	omapfb_set_update_mode(fbdev, manual_update ?
				   OMAPFB_MANUAL_UPDATE : OMAPFB_AUTO_UPDATE);
	init_state++;

	r = fbdev->panel->enable(fbdev->panel);
	if (r)
		goto cleanup;
	init_state++;

	r = omapfb_register_sysfs(fbdev);
	if (r)
		goto cleanup;
	init_state++;

	vram = 0;
	for (i = 0; i < fbdev->mem_desc.region_cnt; i++) {
		r = register_framebuffer(fbdev->fb_info[i]);
		if (r != 0) {
			dev_err(fbdev->dev,
				"registering framebuffer %d failed\n", i);
			goto cleanup;
		}
		vram += fbdev->mem_desc.region[i].size;
	}

	fbdev->state = OMAPFB_ACTIVE;

	panel = fbdev->panel;
	phz = panel->pixel_clock * 1000;
	hhz = phz * 10 / (panel->hfp + panel->x_res + panel->hbp + panel->hsw);
	vhz = hhz / (panel->vfp + panel->y_res + panel->vbp + panel->vsw);

	omapfb_dev = fbdev;

	pr_info("omapfb: Framebuffer initialized. Total vram %lu planes %d\n",
			vram, fbdev->mem_desc.region_cnt);
	pr_info("omapfb: Pixclock %lu kHz hfreq %lu.%lu kHz "
			"vfreq %lu.%lu Hz\n",
			phz / 1000, hhz / 10000, hhz % 10, vhz / 10, vhz % 10);

	return 0;

cleanup:
	omapfb_free_resources(fbdev, init_state);

	return r;
}