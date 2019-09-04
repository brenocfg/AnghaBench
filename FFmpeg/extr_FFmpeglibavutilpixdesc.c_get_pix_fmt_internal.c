#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_2__ {int /*<<< orphan*/  alias; scalar_t__ name; } ;

/* Variables and functions */
 int AV_PIX_FMT_NB ; 
 int AV_PIX_FMT_NONE ; 
 scalar_t__ av_match_name (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* av_pix_fmt_descriptors ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static enum AVPixelFormat get_pix_fmt_internal(const char *name)
{
    enum AVPixelFormat pix_fmt;

    for (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++)
        if (av_pix_fmt_descriptors[pix_fmt].name &&
            (!strcmp(av_pix_fmt_descriptors[pix_fmt].name, name) ||
             av_match_name(name, av_pix_fmt_descriptors[pix_fmt].alias)))
            return pix_fmt;

    return AV_PIX_FMT_NONE;
}