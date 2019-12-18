#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int vcsm_unlock_ptr_sp (void*,int /*<<< orphan*/ ) ; 

int vcsm_unlock_ptr( void *usr_ptr )
{
   return vcsm_unlock_ptr_sp( usr_ptr, 0 );
}