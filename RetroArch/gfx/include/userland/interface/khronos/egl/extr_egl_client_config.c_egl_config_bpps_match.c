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
struct TYPE_2__ {int /*<<< orphan*/  features; } ;
typedef  int /*<<< orphan*/  FEATURES_T ;

/* Variables and functions */
 scalar_t__ FEATURES_UNPACK_ALPHA (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_BLUE (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_DEPTH (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_GREEN (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_RED (int /*<<< orphan*/ ) ; 
 scalar_t__ FEATURES_UNPACK_STENCIL (int /*<<< orphan*/ ) ; 
 TYPE_1__* formats ; 

bool egl_config_bpps_match(int id0, int id1) /* bpps of all buffers match */
{
   FEATURES_T config0 = formats[id0].features;
   FEATURES_T config1 = formats[id1].features;

   return
      FEATURES_UNPACK_RED(config0)     == FEATURES_UNPACK_RED(config1) &&
      FEATURES_UNPACK_GREEN(config0)   == FEATURES_UNPACK_GREEN(config1) &&
      FEATURES_UNPACK_BLUE(config0)    == FEATURES_UNPACK_BLUE(config1) &&
      FEATURES_UNPACK_ALPHA(config0)   == FEATURES_UNPACK_ALPHA(config1) &&
      FEATURES_UNPACK_DEPTH(config0)   == FEATURES_UNPACK_DEPTH(config1) &&
      FEATURES_UNPACK_STENCIL(config0) == FEATURES_UNPACK_STENCIL(config1) &&
      FEATURES_UNPACK_MASK(config0)    == FEATURES_UNPACK_MASK(config1);
}