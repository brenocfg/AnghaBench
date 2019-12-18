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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/  png_structp ;
struct TYPE_3__ {int colour_type; int /*<<< orphan*/  this; scalar_t__ buffer_position; scalar_t__ buffer_count; scalar_t__ flush; scalar_t__ pending_chunk; scalar_t__ pending_len; scalar_t__ bit_depth; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int /*<<< orphan*/  png_infopp ;

/* Variables and functions */
 int /*<<< orphan*/  modifier_start ; 
 int /*<<< orphan*/  set_store_for_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static png_structp
set_modifier_for_read(png_modifier *pm, png_infopp ppi, png_uint_32 id,
    const char *name)
{
   /* Do this first so that the modifier fields are cleared even if an error
    * happens allocating the png_struct.  No allocation is done here so no
    * cleanup is required.
    */
   pm->state = modifier_start;
   pm->bit_depth = 0;
   pm->colour_type = 255;

   pm->pending_len = 0;
   pm->pending_chunk = 0;
   pm->flush = 0;
   pm->buffer_count = 0;
   pm->buffer_position = 0;

   return set_store_for_read(&pm->this, ppi, id, name);
}