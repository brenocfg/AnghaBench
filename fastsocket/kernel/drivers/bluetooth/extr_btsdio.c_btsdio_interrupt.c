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
struct sdio_func {int dummy; } ;
struct btsdio_data {struct sdio_func* func; TYPE_1__* hdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  err_rx; } ;
struct TYPE_3__ {TYPE_2__ stat; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CL_INTRD ; 
 int /*<<< orphan*/  REG_INTRD ; 
 int /*<<< orphan*/  REG_PC_RRT ; 
 scalar_t__ btsdio_rx_packet (struct btsdio_data*) ; 
 struct btsdio_data* sdio_get_drvdata (struct sdio_func*) ; 
 int sdio_readb (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btsdio_interrupt(struct sdio_func *func)
{
	struct btsdio_data *data = sdio_get_drvdata(func);
	int intrd;

	BT_DBG("%s", data->hdev->name);

	intrd = sdio_readb(func, REG_INTRD, NULL);
	if (intrd & 0x01) {
		sdio_writeb(func, 0x01, REG_CL_INTRD, NULL);

		if (btsdio_rx_packet(data) < 0) {
			data->hdev->stat.err_rx++;
			sdio_writeb(data->func, 0x01, REG_PC_RRT, NULL);
		}
	}
}