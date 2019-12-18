#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int max_gamma_8; int output_colour_type; int output_bit_depth; scalar_t__ unpacked; int /*<<< orphan*/  const* transform_list; TYPE_2__* pm; int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ transform_display ;
typedef  int /*<<< orphan*/  png_uint_32 ;
struct TYPE_7__ {int /*<<< orphan*/  use_update_info; int /*<<< orphan*/  this; } ;
typedef  TYPE_2__ png_modifier ;
typedef  int /*<<< orphan*/  image_transform ;

/* Variables and functions */
 int /*<<< orphan*/  do_read_interlace ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  standard_display_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
transform_display_init(transform_display *dp, png_modifier *pm, png_uint_32 id,
    const image_transform *transform_list)
{
   memset(dp, 0, sizeof *dp);

   /* Standard fields */
   standard_display_init(&dp->this, &pm->this, id, do_read_interlace,
      pm->use_update_info);

   /* Parameter fields */
   dp->pm = pm;
   dp->transform_list = transform_list;
   dp->max_gamma_8 = 16;

   /* Local variable fields */
   dp->output_colour_type = 255; /* invalid */
   dp->output_bit_depth = 255;  /* invalid */
   dp->unpacked = 0; /* not unpacked */
}