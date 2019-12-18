#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tq5; int /*<<< orphan*/  tq4; int /*<<< orphan*/  tq3; int /*<<< orphan*/  tq2; int /*<<< orphan*/  tq1; int /*<<< orphan*/  tq0; int /*<<< orphan*/  continued; int /*<<< orphan*/  fBitfield; int /*<<< orphan*/  bt; } ;
struct TYPE_5__ {scalar_t__ index; scalar_t__ rfd; } ;
struct TYPE_7__ {TYPE_2__ ti; TYPE_1__ rndx; scalar_t__ isym; } ;
typedef  TYPE_3__ AUXU ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int,long,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_aux (AUXU u, int auxi, int used)
{
  printf ("\t%s#%-5d %11ld, [%4ld/%7ld], [%2d %1d:%1d %1x:%1x:%1x:%1x:%1x:%1x]\n",
	  (used) ? "  " : "* ",
	  auxi,
	  (long) u.isym,
	  (long) u.rndx.rfd,
	  (long) u.rndx.index,
	  u.ti.bt,
	  u.ti.fBitfield,
	  u.ti.continued,
	  u.ti.tq0,
	  u.ti.tq1,
	  u.ti.tq2,
	  u.ti.tq3,
	  u.ti.tq4,
	  u.ti.tq5);
}