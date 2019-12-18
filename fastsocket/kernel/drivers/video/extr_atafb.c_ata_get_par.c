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
struct atafb_par {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_par ) (struct atafb_par*) ;} ;

/* Variables and functions */
 struct atafb_par current_par ; 
 scalar_t__ current_par_valid ; 
 TYPE_1__* fbhw ; 
 int /*<<< orphan*/  stub1 (struct atafb_par*) ; 

__attribute__((used)) static void ata_get_par(struct atafb_par *par)
{
	if (current_par_valid)
		*par = current_par;
	else
		fbhw->get_par(par);
}