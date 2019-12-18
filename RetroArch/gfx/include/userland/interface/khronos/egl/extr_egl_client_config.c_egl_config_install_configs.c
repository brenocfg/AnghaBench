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
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 size_t ARR_COUNT (TYPE_1__*) ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  khrn_image_to_rso_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  khrn_image_to_tf_format (int /*<<< orphan*/ ) ; 

void egl_config_install_configs(int type)
{
   uint32_t i;
   for (i = 0; i != ARR_COUNT(formats); ++i) {
      formats[i].color = (type == 0) ?
         khrn_image_to_rso_format(formats[i].color) :
         khrn_image_to_tf_format(formats[i].color);
   }
}