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
struct TYPE_3__ {int Width; int Height; int PSM; } ;
typedef  TYPE_1__ GSTEXTURE ;

/* Variables and functions */

__attribute__((used)) static bool texture_need_prepare(GSTEXTURE *texture, int width, int height, int PSM)
{
   return texture->Width != width || texture->Height != height || texture->PSM != PSM;
}