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
struct TYPE_2__ {int mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_E (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OP_M (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ modrm ; 
 int /*<<< orphan*/  obuf ; 
 int /*<<< orphan*/  q_mode ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v_mode ; 

__attribute__((used)) static void
OP_VMX2 (int bytemode, int sizeflag)
{
  if (modrm.mod == 3)
    {
      strcpy (obuf, "rdseed");
      OP_E (v_mode, sizeflag);
    }
  else
    {
      strcpy (obuf, "vmptrst");
      OP_M (q_mode, sizeflag);
    }
}