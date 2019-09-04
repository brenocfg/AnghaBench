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
typedef  int /*<<< orphan*/  HWDevice ;

/* Variables and functions */
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int av_reallocp_array (int /*<<< orphan*/ ***,int,int) ; 
 int /*<<< orphan*/ ** hw_devices ; 
 int nb_hw_devices ; 

__attribute__((used)) static HWDevice *hw_device_add(void)
{
    int err;
    err = av_reallocp_array(&hw_devices, nb_hw_devices + 1,
                            sizeof(*hw_devices));
    if (err) {
        nb_hw_devices = 0;
        return NULL;
    }
    hw_devices[nb_hw_devices] = av_mallocz(sizeof(HWDevice));
    if (!hw_devices[nb_hw_devices])
        return NULL;
    return hw_devices[nb_hw_devices++];
}