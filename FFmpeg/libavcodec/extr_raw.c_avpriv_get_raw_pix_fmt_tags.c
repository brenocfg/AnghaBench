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
struct PixelFormatTag {int dummy; } ;

/* Variables and functions */
 struct PixelFormatTag const* ff_raw_pix_fmt_tags ; 

const struct PixelFormatTag *avpriv_get_raw_pix_fmt_tags(void)
{
    return ff_raw_pix_fmt_tags;
}