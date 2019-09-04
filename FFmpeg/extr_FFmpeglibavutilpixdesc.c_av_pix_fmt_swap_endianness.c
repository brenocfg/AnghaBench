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
typedef  int /*<<< orphan*/  name ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int get_pix_fmt_internal (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

enum AVPixelFormat av_pix_fmt_swap_endianness(enum AVPixelFormat pix_fmt)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    char name[16];
    int i;

    if (!desc || strlen(desc->name) < 2)
        return AV_PIX_FMT_NONE;
    av_strlcpy(name, desc->name, sizeof(name));
    i = strlen(name) - 2;
    if (strcmp(name + i, "be") && strcmp(name + i, "le"))
        return AV_PIX_FMT_NONE;

    name[i] ^= 'b' ^ 'l';

    return get_pix_fmt_internal(name);
}