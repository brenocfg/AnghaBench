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
typedef  uintptr_t VASurfaceID ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static inline VASurfaceID ff_vaapi_get_surface_id(AVFrame *pic)
{
    return (uintptr_t)pic->data[3];
}