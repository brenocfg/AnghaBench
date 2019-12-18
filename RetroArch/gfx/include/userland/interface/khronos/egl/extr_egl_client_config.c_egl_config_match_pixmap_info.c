#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  features; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ KHRN_IMAGE_WRAP_T ;
typedef  int /*<<< orphan*/  KHRN_IMAGE_FORMAT_T ;
typedef  int /*<<< orphan*/  FEATURES_T ;

/* Variables and functions */
 int EGL_MAX_CONFIGS ; 
 scalar_t__ FEATURES_UNPACK_ALPHA (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_BLUE (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_GREEN (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_RED (int /*<<< orphan*/ ) ; 
 TYPE_2__* formats ; 
 scalar_t__ khrn_image_get_alpha_size (int /*<<< orphan*/ ) ; 
 scalar_t__ khrn_image_get_blue_size (int /*<<< orphan*/ ) ; 
 scalar_t__ khrn_image_get_green_size (int /*<<< orphan*/ ) ; 
 scalar_t__ khrn_image_get_red_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

bool egl_config_match_pixmap_info(int id, KHRN_IMAGE_WRAP_T *image)
{
   FEATURES_T features = formats[id].features;
   KHRN_IMAGE_FORMAT_T format = image->format;

   vcos_assert(id >= 0 && id < EGL_MAX_CONFIGS);

   return
      khrn_image_get_red_size(format)   == FEATURES_UNPACK_RED(features) &&
      khrn_image_get_green_size(format) == FEATURES_UNPACK_GREEN(features) &&
      khrn_image_get_blue_size(format)  == FEATURES_UNPACK_BLUE(features) &&
      khrn_image_get_alpha_size(format) == FEATURES_UNPACK_ALPHA(features);
}