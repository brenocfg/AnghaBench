#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transform_display ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_5__ {TYPE_2__* next; } ;
typedef  TYPE_1__ image_transform ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  filler; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_4__ data ; 
 int /*<<< orphan*/  png_set_add_alpha (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_choice () ; 
 int /*<<< orphan*/  random_u32 () ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
image_transform_png_set_add_alpha_set(const image_transform *this,
    transform_display *that, png_structp pp, png_infop pi)
{
   /* Need a random choice for 'before' and 'after' as well as for the
    * filler.  The 'filler' value has all 32 bits set, but only bit_depth
    * will be used.  At this point we don't know bit_depth.
    */
   data.filler = random_u32();
   data.flags = random_choice();

   png_set_add_alpha(pp, data.filler, data.flags);
   this->next->set(this->next, that, pp, pi);
}