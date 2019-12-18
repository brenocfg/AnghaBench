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
typedef  scalar_t__ uint32_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {void* storage; int /*<<< orphan*/ * aux; int /*<<< orphan*/  stride; void* height; void* width; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ KHRN_IMAGE_WRAP_T ;
typedef  int /*<<< orphan*/  KHRN_IMAGE_FORMAT_T ;

/* Variables and functions */

void khrn_image_wrap(KHRN_IMAGE_WRAP_T *wrap, KHRN_IMAGE_FORMAT_T format, uint32_t width, uint32_t height, int32_t stride, void *storage)
{
   wrap->format = format;
   wrap->width = (uint16_t)width;
   wrap->height = (uint16_t)height;
   wrap->stride = stride;
   wrap->aux = NULL;
   wrap->storage = storage;
}