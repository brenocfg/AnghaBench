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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_5__ {int pix_fmt; } ;
typedef  TYPE_1__ VAAPIFormatDescriptor ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__ const*) ; 
 TYPE_1__ const* vaapi_format_map ; 

__attribute__((used)) static const VAAPIFormatDescriptor *
    vaapi_format_from_pix_fmt(enum AVPixelFormat pix_fmt)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(vaapi_format_map); i++)
        if (vaapi_format_map[i].pix_fmt == pix_fmt)
            return &vaapi_format_map[i];
    return NULL;
}