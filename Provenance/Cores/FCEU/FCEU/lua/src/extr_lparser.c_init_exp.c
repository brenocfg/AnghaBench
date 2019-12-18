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
typedef  int /*<<< orphan*/  expkind ;
struct TYPE_5__ {int info; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct TYPE_7__ {TYPE_2__ u; int /*<<< orphan*/  k; int /*<<< orphan*/  t; int /*<<< orphan*/  f; } ;
typedef  TYPE_3__ expdesc ;

/* Variables and functions */
 int /*<<< orphan*/  NO_JUMP ; 

__attribute__((used)) static void init_exp (expdesc *e, expkind k, int i) {
  e->f = e->t = NO_JUMP;
  e->k = k;
  e->u.s.info = i;
}