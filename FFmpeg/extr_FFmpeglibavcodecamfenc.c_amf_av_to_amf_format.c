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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AMF_SURFACE_FORMAT { ____Placeholder_AMF_SURFACE_FORMAT } AMF_SURFACE_FORMAT ;
struct TYPE_3__ {int av_format; int amf_format; } ;

/* Variables and functions */
 int AMF_SURFACE_UNKNOWN ; 
 int amf_countof (TYPE_1__*) ; 
 TYPE_1__* format_map ; 

__attribute__((used)) static enum AMF_SURFACE_FORMAT amf_av_to_amf_format(enum AVPixelFormat fmt)
{
    int i;
    for (i = 0; i < amf_countof(format_map); i++) {
        if (format_map[i].av_format == fmt) {
            return format_map[i].amf_format;
        }
    }
    return AMF_SURFACE_UNKNOWN;
}