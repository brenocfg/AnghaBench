#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; scalar_t__ add; scalar_t__ modify_fn; int /*<<< orphan*/  chunk; } ;
struct TYPE_6__ {int intent; TYPE_5__ this; } ;
typedef  TYPE_1__ srgb_modification ;
struct TYPE_7__ {TYPE_5__* modifications; } ;
typedef  TYPE_2__ png_modifier ;
typedef  int png_byte ;

/* Variables and functions */
 scalar_t__ CHUNK_PLTE ; 
 int /*<<< orphan*/  CHUNK_sBIT ; 
 int /*<<< orphan*/  modification_init (TYPE_5__*) ; 
 scalar_t__ srgb_modify ; 

__attribute__((used)) static void
srgb_modification_init(srgb_modification *me, png_modifier *pm, png_byte intent)
{
   modification_init(&me->this);
   me->this.chunk = CHUNK_sBIT;

   if (intent <= 3) /* if valid, else *delete* sRGB chunks */
   {
      me->this.modify_fn = srgb_modify;
      me->this.add = CHUNK_PLTE;
      me->intent = intent;
   }

   else
   {
      me->this.modify_fn = 0;
      me->this.add = 0;
      me->intent = 0;
   }

   me->this.next = pm->modifications;
   pm->modifications = &me->this;
}