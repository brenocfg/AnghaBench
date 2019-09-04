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
struct TYPE_5__ {unsigned int fourcc; } ;
typedef  TYPE_1__ VAAPIFormatDescriptor ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__ const*) ; 
 TYPE_1__ const* vaapi_format_map ; 

__attribute__((used)) static const VAAPIFormatDescriptor *
    vaapi_format_from_fourcc(unsigned int fourcc)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        if (vaapi_format_map[i].fourcc == fourcc)
            return &vaapi_format_map[i];
    return NULL;
}