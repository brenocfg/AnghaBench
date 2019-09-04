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
struct TYPE_3__ {scalar_t__* formats; } ;
typedef  TYPE_1__ zbar_window_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__* realloc (scalar_t__*,int) ; 

__attribute__((used)) static inline int _zbar_window_add_format (zbar_window_t *w,
                                           uint32_t fmt)
{
    int i;
    for(i = 0; w->formats && w->formats[i]; i++)
        if(w->formats[i] == fmt)
            return(i);

    w->formats = realloc(w->formats, (i + 2) * sizeof(uint32_t));
    w->formats[i] = fmt;
    w->formats[i + 1] = 0;
    return(i);
}