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
typedef  int /*<<< orphan*/  zfpFreqChangeCompleteCb ;
typedef  int /*<<< orphan*/  zdev_t ;
typedef  void* u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_3__ {size_t freqReqQueueTail; int /*<<< orphan*/ * freqChangeCompCb; void** freqReqExtOffset; void** freqReqBw40; int /*<<< orphan*/ * freqReqQueue; } ;
struct TYPE_4__ {TYPE_1__ freqCtrl; } ;

/* Variables and functions */
 size_t ZM_MAX_FREQ_REQ_QUEUE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfAddFreqChangeReq(zdev_t* dev, u16_t frequency, u8_t bw40,
        u8_t extOffset, zfpFreqChangeCompleteCb cb)
{
    zmw_get_wlan_dev(dev);

//printk("zfAddFreqChangeReq  freqReqQueueTail%d\n", wd->freqCtrl.freqReqQueueTail);
    wd->freqCtrl.freqReqQueue[wd->freqCtrl.freqReqQueueTail] = frequency;
    wd->freqCtrl.freqReqBw40[wd->freqCtrl.freqReqQueueTail] = bw40;
    wd->freqCtrl.freqReqExtOffset[wd->freqCtrl.freqReqQueueTail] = extOffset;
    wd->freqCtrl.freqChangeCompCb[wd->freqCtrl.freqReqQueueTail] = cb;
    wd->freqCtrl.freqReqQueueTail++;
    if ( wd->freqCtrl.freqReqQueueTail >= ZM_MAX_FREQ_REQ_QUEUE )
    {
        wd->freqCtrl.freqReqQueueTail = 0;
    }
}