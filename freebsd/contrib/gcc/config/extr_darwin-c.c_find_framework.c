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
struct cpp_dir {int dummy; } ;
struct TYPE_2__ {size_t len; struct cpp_dir* dir; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* frameworks_in_use ; 
 int num_frameworks ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static struct cpp_dir*
find_framework (const char *name, size_t len)
{
  int i;
  for (i = 0; i < num_frameworks; ++i)
    {
      if (len == frameworks_in_use[i].len
	  && strncmp (name, frameworks_in_use[i].name, len) == 0)
	{
	  return frameworks_in_use[i].dir;
	}
    }
  return 0;
}