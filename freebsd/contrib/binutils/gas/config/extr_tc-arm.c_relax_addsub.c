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
struct TYPE_6__ {char* fr_literal; int fr_fix; } ;
typedef  TYPE_1__ fragS ;
struct TYPE_7__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int bfd_get_16 (int /*<<< orphan*/ ,char*) ; 
 int relax_immediate (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
relax_addsub (fragS *fragp, asection *sec)
{
  char *buf;
  int op;

  buf = fragp->fr_literal + fragp->fr_fix;
  op = bfd_get_16(sec->owner, buf);
  if ((op & 0xf) == ((op >> 4) & 0xf))
    return relax_immediate (fragp, 8, 0);
  else
    return relax_immediate (fragp, 3, 0);
}