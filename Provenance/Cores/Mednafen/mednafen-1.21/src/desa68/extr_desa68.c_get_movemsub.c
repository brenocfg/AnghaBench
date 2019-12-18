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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  desa_reg (scalar_t__) ; 

__attribute__((used)) static void get_movemsub(s32 i, s32 j)
{
  desa_reg(i);
  if(i!=j)
    {
      desa_char('-');
      desa_reg(j);
    }
}