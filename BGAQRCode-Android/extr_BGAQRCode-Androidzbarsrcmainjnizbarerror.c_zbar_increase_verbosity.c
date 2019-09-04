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

/* Variables and functions */
 int _zbar_verbosity ; 

void zbar_increase_verbosity ()
{
    if(!_zbar_verbosity)
        _zbar_verbosity++;
    else
        _zbar_verbosity <<= 1;
}