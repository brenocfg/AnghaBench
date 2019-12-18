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
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
typedef  scalar_t__* DEV_CLASS ;

/* Variables and functions */

void uint2devclass(UINT32 cod, DEV_CLASS dev_class)
{
    dev_class[2] = (UINT8)cod;
    dev_class[1] = (UINT8)(cod >> 8);
    dev_class[0] = (UINT8)(cod >> 16);
}