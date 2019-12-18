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
typedef  scalar_t__ u16_t ;

/* Variables and functions */
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (scalar_t__) ; 

u16_t zfGetRandomNumber(zdev_t* dev, u16_t initValue)
{
#if 0
    /* Compiler/Linker error on Linux */
    if ( initValue )
    {
        srand(initValue);
    }

    return ((u16_t)rand());
#endif
    return 0;
}