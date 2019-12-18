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
struct option {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* add_options ) (int,char**,int,struct option**,int,struct option**) ;} ;

/* Variables and functions */
 TYPE_1__* ld_emulation ; 
 int /*<<< orphan*/  stub1 (int,char**,int,struct option**,int,struct option**) ; 

void
ldemul_add_options (int ns, char **shortopts, int nl,
		    struct option **longopts, int nrl,
		    struct option **really_longopts)
{
  if (ld_emulation->add_options)
    (*ld_emulation->add_options) (ns, shortopts, nl, longopts,
				  nrl, really_longopts);
}