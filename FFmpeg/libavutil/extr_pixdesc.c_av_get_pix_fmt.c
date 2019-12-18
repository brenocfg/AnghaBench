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
typedef  int /*<<< orphan*/  name2 ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_VAAPI ; 
 char* X_NE (char*,char*) ; 
 int get_pix_fmt_internal (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

enum AVPixelFormat av_get_pix_fmt(const char *name)
{
    enum AVPixelFormat pix_fmt;

    if (!strcmp(name, "rgb32"))
        name = X_NE("argb", "bgra");
    else if (!strcmp(name, "bgr32"))
        name = X_NE("abgr", "rgba");

    pix_fmt = get_pix_fmt_internal(name);
    if (pix_fmt == AV_PIX_FMT_NONE) {
        char name2[32];

        snprintf(name2, sizeof(name2), "%s%s", name, X_NE("be", "le"));
        pix_fmt = get_pix_fmt_internal(name2);
    }

#if FF_API_VAAPI
    if (pix_fmt == AV_PIX_FMT_NONE && !strcmp(name, "vaapi"))
        pix_fmt = AV_PIX_FMT_VAAPI;
#endif
    return pix_fmt;
}