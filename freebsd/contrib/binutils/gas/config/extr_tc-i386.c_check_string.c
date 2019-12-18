#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* operand_types; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int* types; TYPE_1__ tm; int /*<<< orphan*/ ** seg; } ;

/* Variables and functions */
 int AnyMem ; 
 int EsSeg ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  es ; 
 TYPE_2__ i ; 

__attribute__((used)) static int
check_string (void)
{
  int mem_op = (i.types[0] & AnyMem) ? 0 : 1;
  if ((i.tm.operand_types[mem_op] & EsSeg) != 0)
    {
      if (i.seg[0] != NULL && i.seg[0] != &es)
	{
	  as_bad (_("`%s' operand %d must use `%%es' segment"),
		  i.tm.name,
		  mem_op + 1);
	  return 0;
	}
      /* There's only ever one segment override allowed per instruction.
	 This instruction possibly has a legal segment override on the
	 second operand, so copy the segment to where non-string
	 instructions store it, allowing common code.  */
      i.seg[0] = i.seg[1];
    }
  else if ((i.tm.operand_types[mem_op + 1] & EsSeg) != 0)
    {
      if (i.seg[1] != NULL && i.seg[1] != &es)
	{
	  as_bad (_("`%s' operand %d must use `%%es' segment"),
		  i.tm.name,
		  mem_op + 2);
	  return 0;
	}
    }
  return 1;
}