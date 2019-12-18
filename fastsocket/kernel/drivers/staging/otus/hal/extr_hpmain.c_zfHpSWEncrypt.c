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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;

/* Variables and functions */

void zfHpSWEncrypt(zdev_t* dev, u8_t enable)
{
    /* Because encryption by software or hardware is judged by driver in Otus,
       we don't need to do anything in the HAL layer.
     */
}