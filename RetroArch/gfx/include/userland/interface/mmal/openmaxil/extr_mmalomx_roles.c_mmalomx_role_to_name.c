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
struct TYPE_2__ {char const* name; scalar_t__ role; } ;
typedef  scalar_t__ MMALOMX_ROLE_T ;

/* Variables and functions */
 TYPE_1__* mmalomx_roles ; 

const char *mmalomx_role_to_name(MMALOMX_ROLE_T role)
{
    unsigned int i;
    for (i = 0; mmalomx_roles[i].name; i++)
       if (mmalomx_roles[i].role == role)
          break;
    return mmalomx_roles[i].name;
}