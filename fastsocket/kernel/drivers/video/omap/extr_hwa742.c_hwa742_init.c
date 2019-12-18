#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct omapfb_platform_data {struct hwa742_platform_data* ctrl_platform_data; } ;
struct omapfb_mem_desc {int dummy; } ;
struct omapfb_device {TYPE_7__* dev; TYPE_1__* panel; TYPE_4__* int_ctrl; TYPE_3__* ext_if; } ;
struct hwa742_platform_data {scalar_t__ te_connected; } ;
struct TYPE_17__ {int /*<<< orphan*/  entry; } ;
struct TYPE_16__ {struct omapfb_platform_data* platform_data; } ;
struct TYPE_14__ {scalar_t__ data; int /*<<< orphan*/  function; } ;
struct TYPE_11__ {scalar_t__ format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_15__ {int te_connected; int prev_color_mode; TYPE_4__* int_ctrl; TYPE_3__* extif; int /*<<< orphan*/  sys_ck; int /*<<< orphan*/  req_sema; int /*<<< orphan*/  free_req_list; TYPE_9__* req_pool; int /*<<< orphan*/  pending_req_list; struct omapfb_device* fbdev; scalar_t__ prev_flags; TYPE_5__ auto_update_timer; TYPE_2__ auto_update_window; int /*<<< orphan*/  update_mode; int /*<<< orphan*/  max_transmit_size; int /*<<< orphan*/  reg_timings; int /*<<< orphan*/  req_lock; } ;
struct TYPE_13__ {int (* init ) (struct omapfb_device*,int,struct omapfb_mem_desc*) ;int /*<<< orphan*/  (* cleanup ) () ;} ;
struct TYPE_12__ {int (* init ) (struct omapfb_device*) ;int /*<<< orphan*/  (* cleanup ) () ;int /*<<< orphan*/  max_transmit_size; int /*<<< orphan*/  (* set_timings ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  y_res; int /*<<< orphan*/  x_res; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_9__*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  HWA742_CONFIG_REG ; 
 int /*<<< orphan*/  HWA742_PLL_DIV_REG ; 
 int /*<<< orphan*/  HWA742_REV_CODE_REG ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IRQ_REQ_POOL_SIZE ; 
 int /*<<< orphan*/  OMAPFB_UPDATE_DISABLED ; 
 int calc_extif_timings (unsigned long,int*) ; 
 int /*<<< orphan*/  calc_hwa742_clk_rates (unsigned long,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_7__*,char*,int,int) ; 
 TYPE_6__ hwa742 ; 
 int hwa742_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwa742_update_window_auto ; 
 int /*<<< orphan*/  init_timer (TYPE_5__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int setup_tearsync (unsigned long,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct omapfb_device*,int,struct omapfb_mem_desc*) ; 
 int stub2 (struct omapfb_device*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  stub6 () ; 

__attribute__((used)) static int hwa742_init(struct omapfb_device *fbdev, int ext_mode,
		       struct omapfb_mem_desc *req_vram)
{
	int r = 0, i;
	u8 rev, conf;
	unsigned long ext_clk;
	unsigned long sys_clk, pix_clk;
	int extif_mem_div;
	struct omapfb_platform_data *omapfb_conf;
	struct hwa742_platform_data *ctrl_conf;

	BUG_ON(!fbdev->ext_if || !fbdev->int_ctrl);

	hwa742.fbdev = fbdev;
	hwa742.extif = fbdev->ext_if;
	hwa742.int_ctrl = fbdev->int_ctrl;

	omapfb_conf = fbdev->dev->platform_data;
	ctrl_conf = omapfb_conf->ctrl_platform_data;

	if (ctrl_conf == NULL) {
		dev_err(fbdev->dev, "HWA742: missing platform data\n");
		r = -ENOENT;
		goto err1;
	}

	hwa742.sys_ck = clk_get(NULL, "hwa_sys_ck");

	spin_lock_init(&hwa742.req_lock);

	if ((r = hwa742.int_ctrl->init(fbdev, 1, req_vram)) < 0)
		goto err1;

	if ((r = hwa742.extif->init(fbdev)) < 0)
		goto err2;

	ext_clk = clk_get_rate(hwa742.sys_ck);
	if ((r = calc_extif_timings(ext_clk, &extif_mem_div)) < 0)
		goto err3;
	hwa742.extif->set_timings(&hwa742.reg_timings);
	clk_enable(hwa742.sys_ck);

	calc_hwa742_clk_rates(ext_clk, &sys_clk, &pix_clk);
	if ((r = calc_extif_timings(sys_clk, &extif_mem_div)) < 0)
		goto err4;
	hwa742.extif->set_timings(&hwa742.reg_timings);

	rev = hwa742_read_reg(HWA742_REV_CODE_REG);
	if ((rev & 0xfc) != 0x80) {
		dev_err(fbdev->dev, "HWA742: invalid revision %02x\n", rev);
		r = -ENODEV;
		goto err4;
	}


	if (!(hwa742_read_reg(HWA742_PLL_DIV_REG) & 0x80)) {
		dev_err(fbdev->dev,
		      "HWA742: controller not initialized by the bootloader\n");
		r = -ENODEV;
		goto err4;
	}

	if (ctrl_conf->te_connected) {
		if ((r = setup_tearsync(pix_clk, extif_mem_div)) < 0) {
			dev_err(hwa742.fbdev->dev,
			       "HWA742: can't setup tearing synchronization\n");
			goto err4;
		}
		hwa742.te_connected = 1;
	}

	hwa742.max_transmit_size = hwa742.extif->max_transmit_size;

	hwa742.update_mode = OMAPFB_UPDATE_DISABLED;

	hwa742.auto_update_window.x = 0;
	hwa742.auto_update_window.y = 0;
	hwa742.auto_update_window.width = fbdev->panel->x_res;
	hwa742.auto_update_window.height = fbdev->panel->y_res;
	hwa742.auto_update_window.format = 0;

	init_timer(&hwa742.auto_update_timer);
	hwa742.auto_update_timer.function = hwa742_update_window_auto;
	hwa742.auto_update_timer.data = 0;

	hwa742.prev_color_mode = -1;
	hwa742.prev_flags = 0;

	hwa742.fbdev = fbdev;

	INIT_LIST_HEAD(&hwa742.free_req_list);
	INIT_LIST_HEAD(&hwa742.pending_req_list);
	for (i = 0; i < ARRAY_SIZE(hwa742.req_pool); i++)
		list_add(&hwa742.req_pool[i].entry, &hwa742.free_req_list);
	BUG_ON(i <= IRQ_REQ_POOL_SIZE);
	sema_init(&hwa742.req_sema, i - IRQ_REQ_POOL_SIZE);

	conf = hwa742_read_reg(HWA742_CONFIG_REG);
	dev_info(fbdev->dev, ": Epson HWA742 LCD controller rev %d "
			"initialized (CNF pins %x)\n", rev & 0x03, conf & 0x07);

	return 0;
err4:
	clk_disable(hwa742.sys_ck);
err3:
	hwa742.extif->cleanup();
err2:
	hwa742.int_ctrl->cleanup();
err1:
	return r;
}