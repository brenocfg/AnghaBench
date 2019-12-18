#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__** kids; scalar_t__ copy; } ;
struct TYPE_15__ {TYPE_6__ x; TYPE_2__** syms; } ;
struct TYPE_13__ {TYPE_4__** syms; } ;
struct TYPE_11__ {scalar_t__ name; } ;
struct TYPE_12__ {TYPE_3__ x; } ;
struct TYPE_9__ {scalar_t__ name; } ;
struct TYPE_10__ {TYPE_1__ x; } ;
typedef  TYPE_7__* Node ;

/* Variables and functions */
 size_t RX ; 

__attribute__((used)) static int moveself(Node p) {
	return p->x.copy
	&& p->syms[RX]->x.name == p->x.kids[0]->syms[RX]->x.name;
}