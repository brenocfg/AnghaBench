#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ common; TYPE_1__ named; } ;
typedef  TYPE_3__ section ;
typedef  int hashval_t ;

/* Variables and functions */
 int SECTION_NAMED ; 
 int htab_hash_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
hash_section (section *sect)
{
  if (sect->common.flags & SECTION_NAMED)
    return htab_hash_string (sect->named.name);
  return sect->common.flags;
}