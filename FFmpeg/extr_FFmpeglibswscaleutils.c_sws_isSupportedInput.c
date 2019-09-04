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
struct TYPE_2__ {int is_supported_in; } ;

/* Variables and functions */
 unsigned int AV_PIX_FMT_NB ; 
 TYPE_1__* format_entries ; 

int sws_isSupportedInput(enum AVPixelFormat pix_fmt)
{
    return (unsigned)pix_fmt < AV_PIX_FMT_NB ?
           format_entries[pix_fmt].is_supported_in : 0;
}