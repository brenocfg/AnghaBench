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
struct input_dev {int dummy; } ;
struct gf2k {size_t id; struct input_dev* dev; } ;

/* Variables and functions */
 scalar_t__ ABS_HAT0X ; 
 int GB (int,int,int) ; 
 scalar_t__* gf2k_abs ; 
 int* gf2k_axes ; 
 int /*<<< orphan*/ * gf2k_btn_joy ; 
 int /*<<< orphan*/ * gf2k_btn_pad ; 
 int** gf2k_hat_to_axis ; 
 int* gf2k_hats ; 
 int* gf2k_joys ; 
 int* gf2k_pads ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gf2k_read(struct gf2k *gf2k, unsigned char *data)
{
	struct input_dev *dev = gf2k->dev;
	int i, t;

	for (i = 0; i < 4 && i < gf2k_axes[gf2k->id]; i++)
		input_report_abs(dev, gf2k_abs[i], GB(i<<3,8,0) | GB(i+46,1,8) | GB(i+50,1,9));

	for (i = 0; i < 2 && i < gf2k_axes[gf2k->id] - 4; i++)
		input_report_abs(dev, gf2k_abs[i], GB(i*9+60,8,0) | GB(i+54,1,9));

	t = GB(40,4,0);

	for (i = 0; i < gf2k_hats[gf2k->id]; i++)
		input_report_abs(dev, ABS_HAT0X + i, gf2k_hat_to_axis[t][i]);

	t = GB(44,2,0) | GB(32,8,2) | GB(78,2,10);

	for (i = 0; i < gf2k_joys[gf2k->id]; i++)
		input_report_key(dev, gf2k_btn_joy[i], (t >> i) & 1);

	for (i = 0; i < gf2k_pads[gf2k->id]; i++)
		input_report_key(dev, gf2k_btn_pad[i], (t >> i) & 1);

	input_sync(dev);
}