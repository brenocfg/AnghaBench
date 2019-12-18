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
typedef  scalar_t__ voidp ;

/* Variables and functions */
 int /*<<< orphan*/  Z_Malloc (unsigned int) ; 

voidp zcalloc (voidp opaque, unsigned items, unsigned size)
{
    if (opaque) items += size - size; /* make compiler happy */
    return (voidp)Z_Malloc(items*size);
}