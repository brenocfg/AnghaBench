#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  win; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  data_of (TYPE_1__*) ; 
#define  sDIRS 129 
#define  sFILES 128 

__attribute__((used)) static bool
usable_state(int state, LIST * dirs, LIST * files)
{
    bool result;

    switch (state) {
    case sDIRS:
	result = (dirs->win != 0) && (data_of(dirs) != 0);
	break;
    case sFILES:
	result = (files->win != 0) && (data_of(files) != 0);
	break;
    default:
	result = TRUE;
	break;
    }
    return result;
}