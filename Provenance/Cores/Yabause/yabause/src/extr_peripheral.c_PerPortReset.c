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
struct TYPE_4__ {int* data; int size; } ;
struct TYPE_3__ {int* data; int size; } ;

/* Variables and functions */
 TYPE_2__ PORTDATA1 ; 
 TYPE_1__ PORTDATA2 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * perkeyconfig ; 
 scalar_t__ perkeyconfigsize ; 

void PerPortReset(void)
{
        PORTDATA1.data[0] = 0xF0;
        PORTDATA1.size = 1;
        PORTDATA2.data[0] = 0xF0;
        PORTDATA2.size = 1;

	perkeyconfigsize = 0;
        if (perkeyconfig)
           free(perkeyconfig);
	perkeyconfig = NULL;
}