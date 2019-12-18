#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* ch; } ;
struct TYPE_6__ {void* debug; } ;
struct TYPE_7__ {TYPE_1__ dch; } ;
struct sfax_hw {TYPE_5__ isar; TYPE_2__ isac; } ;
struct TYPE_8__ {void* debug; } ;
struct TYPE_9__ {TYPE_3__ bch; } ;

/* Variables and functions */
 void* debug ; 

__attribute__((used)) static void
_set_debug(struct sfax_hw *card)
{
	card->isac.dch.debug = debug;
	card->isar.ch[0].bch.debug = debug;
	card->isar.ch[1].bch.debug = debug;
}