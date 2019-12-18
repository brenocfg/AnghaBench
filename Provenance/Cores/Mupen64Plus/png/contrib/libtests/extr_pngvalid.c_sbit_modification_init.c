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
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  add; int /*<<< orphan*/  modify_fn; int /*<<< orphan*/  chunk; } ;
struct TYPE_6__ {TYPE_5__ this; int /*<<< orphan*/  sbit; } ;
typedef  TYPE_1__ sbit_modification ;
struct TYPE_7__ {TYPE_5__* modifications; } ;
typedef  TYPE_2__ png_modifier ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_PLTE ; 
 int /*<<< orphan*/  CHUNK_sBIT ; 
 int /*<<< orphan*/  modification_init (TYPE_5__*) ; 
 int /*<<< orphan*/  sbit_modify ; 

__attribute__((used)) static void
sbit_modification_init(sbit_modification *me, png_modifier *pm, png_byte sbit)
{
   modification_init(&me->this);
   me->this.chunk = CHUNK_sBIT;
   me->this.modify_fn = sbit_modify;
   me->this.add = CHUNK_PLTE;
   me->sbit = sbit;
   me->this.next = pm->modifications;
   pm->modifications = &me->this;
}