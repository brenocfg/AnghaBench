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
typedef  int u8 ;
struct wps_sm {int discard_ap_cnt; TYPE_1__* dis_ap_list; } ;
struct TYPE_2__ {int* bssid; } ;

/* Variables and functions */
 int WPS_MAX_DIS_AP_NUM ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void wps_add_discard_ap(u8 *bssid)
{
    struct wps_sm *sm = gWpsSm;
    u8 cnt = sm->discard_ap_cnt;

    if (!gWpsSm || !bssid) {
        return;
    }

    if (sm->discard_ap_cnt < WPS_MAX_DIS_AP_NUM) {
        sm->discard_ap_cnt++;
    } else {
        for (cnt = 0; cnt < WPS_MAX_DIS_AP_NUM - 2; cnt++) {
            memcpy(sm->dis_ap_list[cnt].bssid, sm->dis_ap_list[cnt + 1].bssid, 6);
        }
        sm->discard_ap_cnt = WPS_MAX_DIS_AP_NUM;
    }
    memcpy(sm->dis_ap_list[cnt].bssid, bssid, 6);
}