#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u8_t ;
typedef  scalar_t__ u32_t ;
struct zsHpPriv {int dummy; } ;
struct TYPE_5__ {struct zsHpPriv* hpPrivate; } ;
struct TYPE_4__ {scalar_t__ bChannel; scalar_t__ flag; } ;
typedef  TYPE_1__ CAL_CTL_EDGES ;

/* Variables and functions */
 scalar_t__ AR5416_BCHAN_UNUSED ; 
 size_t AR5416_NUM_BAND_EDGES ; 
 scalar_t__ ZM_CH_G_14 ; 
 scalar_t__ fbin2freq (scalar_t__,size_t) ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u32_t zfHpCheckDoHeavyClip(zdev_t* dev, u32_t freq, CAL_CTL_EDGES *pCtlEdges, u8_t bw40)
{
    u32_t ret = 0;
    u8_t i;
    u8_t is2GHz;
    struct zsHpPriv* hpPriv;

    zmw_get_wlan_dev(dev);

    hpPriv = wd->hpPrivate;

    if(freq > ZM_CH_G_14)
        is2GHz = 0;
    else
        is2GHz = 1;

    /* HT40 force enable heavy clip */
    if (bw40)
    {
        ret |= 0xf0;
    }
#if 1
    /* HT20 : frequency bandedge */
    for (i = 0; (i < AR5416_NUM_BAND_EDGES) && (pCtlEdges[i].bChannel != AR5416_BCHAN_UNUSED) ; i++)
    {
        if (freq == fbin2freq(pCtlEdges[i].bChannel, is2GHz))
        {
            if (pCtlEdges[i].flag == 0)
            {
                ret |= 0xf;
            }
            break;
        }
    }
#endif

    return ret;
}