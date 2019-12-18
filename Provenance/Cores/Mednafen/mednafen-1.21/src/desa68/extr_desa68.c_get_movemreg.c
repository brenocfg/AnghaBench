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
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  desa_char (char) ; 
 int /*<<< orphan*/  get_movemsub (int,int) ; 

__attribute__((used)) static void get_movemreg(u32 v, u32 rev)
{
  s32 i,j,p=0;
  for(i=0 ; i<16; i++)
    {
      for(; i<16 && (v&(1<<(i^rev)))==0; i++);
      if(i==16) break;
      j = i;
      for(; i<16 && (v&(1<<(i^rev))); i++);
      if(p) desa_char('/');
      get_movemsub(j,(i-1));
      p = 1;
    }
}