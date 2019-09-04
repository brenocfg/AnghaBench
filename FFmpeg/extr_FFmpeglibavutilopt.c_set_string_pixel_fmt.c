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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVOption ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PIX_FMT_NB ; 
 int /*<<< orphan*/  av_get_pix_fmt ; 
 int set_string_fmt (void*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int set_string_pixel_fmt(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    return set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, av_get_pix_fmt, "pixel format");
}