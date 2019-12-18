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
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  SET_COMMON_FORMATS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_formats_ref ; 
 int /*<<< orphan*/  ff_formats_unref ; 
 int /*<<< orphan*/  in_formats ; 
 int /*<<< orphan*/  out_formats ; 

int ff_set_common_formats(AVFilterContext *ctx, AVFilterFormats *formats)
{
    SET_COMMON_FORMATS(ctx, formats, in_formats, out_formats,
                       ff_formats_ref, ff_formats_unref, formats);
}