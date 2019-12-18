#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvbios_init {TYPE_2__* outp; } ;
struct TYPE_3__ {int link; } ;
struct TYPE_4__ {TYPE_1__ sorconf; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static inline int
init_link(struct nvbios_init *init)
{
	if (init->outp)
		return !(init->outp->sorconf.link & 1);
	error("script needs OR link\n");
	return 0;
}