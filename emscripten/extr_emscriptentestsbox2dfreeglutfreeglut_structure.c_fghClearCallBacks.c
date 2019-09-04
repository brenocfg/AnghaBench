#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** CallBacks; } ;
typedef  TYPE_1__ SFG_Window ;

/* Variables and functions */
 int TOTAL_CALLBACKS ; 

__attribute__((used)) static void fghClearCallBacks( SFG_Window *window )
{
    if( window )
    {
        int i;
        for( i = 0; i < TOTAL_CALLBACKS; ++i )
            window->CallBacks[ i ] = NULL;
    }
}