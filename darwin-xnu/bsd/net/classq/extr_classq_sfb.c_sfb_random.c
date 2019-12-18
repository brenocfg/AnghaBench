#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct sfb {TYPE_1__* sfb_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_CONVERT_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RandomULong () ; 

__attribute__((used)) static u_int32_t
sfb_random(struct sfb *sp)
{
	IFCQ_CONVERT_LOCK(&sp->sfb_ifp->if_snd);
	return (RandomULong());
}