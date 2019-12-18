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
struct TYPE_2__ {int /*<<< orphan*/ * info; } ;

/* Variables and functions */
 TYPE_1__ ssf_info ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

void get_ssf_info(int num, char * data_out)
{
   if (!data_out)
      return;

   strcpy(data_out, ssf_info.info[num]);
}