#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int limit; scalar_t__ colour_type; scalar_t__ bit_depth; scalar_t__ encoding_ignored; scalar_t__ current_encoding; scalar_t__ current_gamma; scalar_t__ test_uses_encoding; int /*<<< orphan*/  state; int /*<<< orphan*/ * modifications; scalar_t__ buffer_position; scalar_t__ buffer_count; scalar_t__ flush; scalar_t__ pending_chunk; scalar_t__ pending_len; int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */
 int /*<<< orphan*/  modifier_encoding_iterate (TYPE_1__*) ; 
 int /*<<< orphan*/  modifier_start ; 
 int /*<<< orphan*/  store_read_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
modifier_reset(png_modifier *pm)
{
   store_read_reset(&pm->this);
   pm->limit = 4E-3;
   pm->pending_len = pm->pending_chunk = 0;
   pm->flush = pm->buffer_count = pm->buffer_position = 0;
   pm->modifications = NULL;
   pm->state = modifier_start;
   modifier_encoding_iterate(pm);
   /* The following must be set in the next run.  In particular
    * test_uses_encodings must be set in the _ini function of each transform
    * that looks at the encodings.  (Not the 'add' function!)
    */
   pm->test_uses_encoding = 0;
   pm->current_gamma = 0;
   pm->current_encoding = 0;
   pm->encoding_ignored = 0;
   /* These only become value after IHDR is read: */
   pm->bit_depth = pm->colour_type = 0;
}