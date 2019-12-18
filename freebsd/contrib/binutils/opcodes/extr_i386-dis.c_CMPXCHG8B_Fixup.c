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

/* Variables and functions */
 int /*<<< orphan*/  OP_M (int,int) ; 
 int REX_W ; 
 int /*<<< orphan*/  USED_REX (int) ; 
 int o_mode ; 
 char* obuf ; 
 int rex ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
CMPXCHG8B_Fixup (int bytemode, int sizeflag)
{
  USED_REX (REX_W);
  if (rex & REX_W)
    {
      /* Change cmpxchg8b to cmpxchg16b.  */
      char *p = obuf + strlen (obuf) - 2;
      strcpy (p, "16b");
      bytemode = o_mode;
    }
  OP_M (bytemode, sizeflag);
}