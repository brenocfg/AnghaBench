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
typedef  int /*<<< orphan*/  dt_pfargv_t ;
struct TYPE_6__ {char* pfd_fmt; } ;
typedef  TYPE_1__ dt_pfargd_t ;
struct TYPE_7__ {int dn_flags; } ;
typedef  TYPE_2__ dt_node_t ;

/* Variables and functions */
 int DT_NF_SIGNED ; 
 int dt_node_is_integer (TYPE_2__*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
pfcheck_dint(dt_pfargv_t *pfv, dt_pfargd_t *pfd, dt_node_t *dnp)
{
	if (dnp->dn_flags & DT_NF_SIGNED)
		pfd->pfd_fmt[strlen(pfd->pfd_fmt) - 1] = 'i';
	else
		pfd->pfd_fmt[strlen(pfd->pfd_fmt) - 1] = 'u';

	return (dt_node_is_integer(dnp));
}