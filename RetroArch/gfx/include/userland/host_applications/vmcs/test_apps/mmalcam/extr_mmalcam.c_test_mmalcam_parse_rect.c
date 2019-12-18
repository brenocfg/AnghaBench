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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ MMAL_RECT_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_BOOL_T test_mmalcam_parse_rect(const char *str, MMAL_RECT_T *rect)
{
   /* coverity[secure_coding] Only reading integers, so can't overflow */
   return sscanf(str, "%d,%d,%d,%d", &rect->x, &rect->y, &rect->width, &rect->height) == 4;
}