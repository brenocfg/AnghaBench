#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* rcc_interface_ty ;
struct TYPE_11__ {int /*<<< orphan*/  (* defstring ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_7__ {scalar_t__ str; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {TYPE_2__ rcc_Defstring; } ;
struct TYPE_10__ {TYPE_3__ v; } ;

/* Variables and functions */
 TYPE_6__* IR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void doDefstring(rcc_interface_ty in) {
	(*IR->defstring)(in->v.rcc_Defstring.s.len, (char *)in->v.rcc_Defstring.s.str);
	free((char *)in->v.rcc_Defstring.s.str);
}