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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  size_t u16_t ;
struct TYPE_3__ {size_t ibssAdditionalIESize; int /*<<< orphan*/ * ibssAdditionalIE; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16_t zfStaAddIbssAdditionalIE(zdev_t* dev, zbuf_t* buf, u16_t offset)
{
	u16_t i;

    zmw_get_wlan_dev(dev);

    for (i=0; i<wd->sta.ibssAdditionalIESize; i++)
    {
        zmw_tx_buf_writeb(dev, buf, offset++, wd->sta.ibssAdditionalIE[i]);
    }

    return offset;
}