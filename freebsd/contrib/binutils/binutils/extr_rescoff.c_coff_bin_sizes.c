#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct extern_res_entry {int dummy; } ;
struct extern_res_directory {int dummy; } ;
struct extern_res_data {int dummy; } ;
struct coff_write_info {int dirsize; int dirstrsize; int dataentsize; } ;
struct TYPE_11__ {TYPE_6__* dir; } ;
struct TYPE_8__ {int length; } ;
struct TYPE_9__ {TYPE_1__ n; } ;
struct TYPE_10__ {TYPE_2__ u; scalar_t__ named; } ;
struct TYPE_12__ {TYPE_4__ u; scalar_t__ subdir; TYPE_3__ id; struct TYPE_12__* next; } ;
typedef  TYPE_5__ rc_res_entry ;
struct TYPE_13__ {TYPE_5__* entries; } ;
typedef  TYPE_6__ rc_res_directory ;

/* Variables and functions */

__attribute__((used)) static void
coff_bin_sizes (const rc_res_directory *resdir,
		struct coff_write_info *cwi)
{
  const rc_res_entry *re;

  cwi->dirsize += sizeof (struct extern_res_directory);

  for (re = resdir->entries; re != NULL; re = re->next)
    {
      cwi->dirsize += sizeof (struct extern_res_entry);

      if (re->id.named)
	cwi->dirstrsize += re->id.u.n.length * 2 + 2;

      if (re->subdir)
	coff_bin_sizes (re->u.dir, cwi);
      else
	cwi->dataentsize += sizeof (struct extern_res_data);
    }
}