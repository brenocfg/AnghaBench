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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct dvb_bt8xx_card {int /*<<< orphan*/  bttv_nr; } ;
struct TYPE_2__ {struct dvb_bt8xx_card* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_write_gpio (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void or51211_sleep(struct dvb_frontend * fe)
{
	struct dvb_bt8xx_card *bt = fe->dvb->priv;
	bttv_write_gpio(bt->bttv_nr, 0x0001, 0x0000);
}