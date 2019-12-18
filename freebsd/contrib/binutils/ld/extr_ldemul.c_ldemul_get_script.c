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
struct TYPE_2__ {char* (* get_script ) (int*) ;} ;

/* Variables and functions */
 TYPE_1__* ld_emulation ; 
 char* stub1 (int*) ; 

char *
ldemul_get_script (int *isfile)
{
  return ld_emulation->get_script (isfile);
}