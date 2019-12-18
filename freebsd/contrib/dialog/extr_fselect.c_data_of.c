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
struct TYPE_3__ {char** data; size_t choice; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */

__attribute__((used)) static char *
data_of(LIST * list)
{
    if (list != 0
	&& list->data != 0)
	return list->data[list->choice];
    return 0;
}