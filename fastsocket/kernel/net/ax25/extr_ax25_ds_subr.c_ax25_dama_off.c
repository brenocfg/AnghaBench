#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ax25_dev; int /*<<< orphan*/  condition; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_COND_DAMA_MODE ; 
 int /*<<< orphan*/  ax25_dev_dama_off (int /*<<< orphan*/ ) ; 

void ax25_dama_off(ax25_cb *ax25)
{
	ax25->condition &= ~AX25_COND_DAMA_MODE;
	ax25_dev_dama_off(ax25->ax25_dev);
}