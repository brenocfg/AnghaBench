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
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL_SECTION () ; 
 int /*<<< orphan*/  EXIT_CRITICAL_SECTION () ; 
 int /*<<< orphan*/  ucPortMode ; 

void
vMBPortSetMode( UCHAR ucMode )
{
    ENTER_CRITICAL_SECTION();
    ucPortMode = ucMode;
    EXIT_CRITICAL_SECTION();
}