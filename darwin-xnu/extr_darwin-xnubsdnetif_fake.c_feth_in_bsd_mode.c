#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_fake_ref ;
typedef  int boolean_t ;
struct TYPE_3__ {int iff_flags; } ;

/* Variables and functions */
 int IFF_FLAGS_BSD_MODE ; 

__attribute__((used)) static inline boolean_t
feth_in_bsd_mode(if_fake_ref fakeif)
{
	return ((fakeif->iff_flags & IFF_FLAGS_BSD_MODE) != 0);
}