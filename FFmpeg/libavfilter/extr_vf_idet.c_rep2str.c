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
typedef  int RepeatedField ;

/* Variables and functions */
#define  REPEAT_BOTTOM 130 
#define  REPEAT_NONE 129 
#define  REPEAT_TOP 128 

__attribute__((used)) static const char *rep2str(RepeatedField repeated_field)
{
    switch(repeated_field) {
        case REPEAT_NONE    : return "neither";
        case REPEAT_TOP     : return "top";
        case REPEAT_BOTTOM  : return "bottom";
    }
    return NULL;
}