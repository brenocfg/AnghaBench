#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_4__ {char* name; int nb_components; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int av_get_bits_per_pixel (TYPE_1__ const*) ; 
 TYPE_1__* av_pix_fmt_descriptors ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

char *av_get_pix_fmt_string(char *buf, int buf_size,
                            enum AVPixelFormat pix_fmt)
{
    /* print header */
    if (pix_fmt < 0) {
       snprintf (buf, buf_size, "name" " nb_components" " nb_bits");
    } else {
        const AVPixFmtDescriptor *pixdesc = &av_pix_fmt_descriptors[pix_fmt];
        snprintf(buf, buf_size, "%-11s %7d %10d", pixdesc->name,
                 pixdesc->nb_components, av_get_bits_per_pixel(pixdesc));
    }

    return buf;
}