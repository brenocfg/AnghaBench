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
typedef  enum frontend_architecture { ____Placeholder_frontend_architecture } frontend_architecture ;

/* Variables and functions */
 int FRONTEND_ARCH_PPC ; 

enum frontend_architecture frontend_ps3_get_architecture(void)
{
   return FRONTEND_ARCH_PPC;
}