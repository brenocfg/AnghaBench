#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int filler; } ;
struct TYPE_10__ {TYPE_1__ this; } ;
typedef  TYPE_2__ transform_display ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_11__ {TYPE_4__* next; } ;
typedef  TYPE_3__ image_transform ;
struct TYPE_13__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  filler; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* set ) (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_8__ data ; 
 int /*<<< orphan*/  png_set_filler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_choice () ; 
 int /*<<< orphan*/  random_u32 () ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
image_transform_png_set_filler_set(const image_transform *this,
    transform_display *that, png_structp pp, png_infop pi)
{
   /* Need a random choice for 'before' and 'after' as well as for the
    * filler.  The 'filler' value has all 32 bits set, but only bit_depth
    * will be used.  At this point we don't know bit_depth.
    */
   data.filler = random_u32();
   data.flags = random_choice();

   png_set_filler(pp, data.filler, data.flags);

   /* The standard display handling stuff also needs to know that
    * there is a filler, so set that here.
    */
   that->this.filler = 1;

   this->next->set(this->next, that, pp, pi);
}