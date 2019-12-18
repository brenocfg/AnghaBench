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
typedef  int /*<<< orphan*/  zdev_t ;
struct zsHpPriv {int /*<<< orphan*/ * remainBuf; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfUsbFree(zdev_t* dev)
{
    struct zsHpPriv *halPriv;

    zmw_get_wlan_dev(dev);

    halPriv = (struct zsHpPriv*)wd->hpPrivate;

#ifdef ZM_OTUS_RX_STREAM_MODE
    if ( halPriv->remainBuf != NULL )
    {
        zfwBufFree(dev, halPriv->remainBuf, 0);
    }
#endif

    return;
}