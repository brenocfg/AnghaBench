#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* netbsd_core_data; } ;
struct TYPE_9__ {TYPE_3__ tdata; } ;
typedef  TYPE_4__ bfd ;
struct TYPE_6__ {char* c_name; } ;
struct TYPE_7__ {TYPE_1__ core; } ;

/* Variables and functions */

__attribute__((used)) static char*
netbsd_core_file_failing_command (bfd *abfd)
{
  /*return core_command (abfd);*/
  return abfd->tdata.netbsd_core_data->core.c_name;
}