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
typedef  enum AVColorTransferCharacteristic { ____Placeholder_AVColorTransferCharacteristic } AVColorTransferCharacteristic ;

/* Variables and functions */
 unsigned int AVCOL_TRC_NB ; 
 char const** color_transfer_names ; 

const char *av_color_transfer_name(enum AVColorTransferCharacteristic transfer)
{
    return (unsigned) transfer < AVCOL_TRC_NB ?
        color_transfer_names[transfer] : NULL;
}