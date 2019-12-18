#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
struct TYPE_3__ {int* c_ind_mask_table; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 int C_IND_MASK_DWORDS ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,char*) ; 

__attribute__((used)) static void dump_c_ind_mask (PLCI   *plci)
{
static char hex_digit_table[0x10] =
  {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
  word i, j, k;
  dword d;
    char *p;
    char buf[40];

  for (i = 0; i < C_IND_MASK_DWORDS; i += 4)
  {
    p = buf + 36;
    *p = '\0';
    for (j = 0; j < 4; j++)
    {
      if (i+j < C_IND_MASK_DWORDS)
      {
        d = plci->c_ind_mask_table[i+j];
        for (k = 0; k < 8; k++)
        {
          *(--p) = hex_digit_table[d & 0xf];
          d >>= 4;
        }
      }
      else if (i != 0)
      {
        for (k = 0; k < 8; k++)
          *(--p) = ' ';
      }
      *(--p) = ' ';
    }
    dbug(1,dprintf ("c_ind_mask =%s", (char   *) p));
  }
}