#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ ** c; } ;
typedef  TYPE_1__ jacobian ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ curve_params ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
point_zero(jacobian *P, const curve_params *cc)
{
	memset(P, 0, sizeof *P);
	P->c[0][0] = P->c[1][0] = P->c[2][0] = cc->p[0];
}