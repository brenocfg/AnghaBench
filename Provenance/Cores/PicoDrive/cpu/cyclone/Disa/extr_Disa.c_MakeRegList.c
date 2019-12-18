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
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int MakeRegList(char *list,int mask,int ea)
{
  int reverse=0,i=0,low=0,len=0;

  if ((ea&0x38)==0x20) reverse=1; // -(An), bitfield is reversed

  mask&=0xffff; list[0]=0;

  for (i=0;i<17;i++)
  {
    int bit=0;
    
    // Mask off bit i:
    if (reverse) bit=0x8000>>i; else bit=1<<i;
    bit&=mask;

    if (bit==0 || i==8)
    {
      // low to i-1 are a continuous section, add it:
      char add[16]="";
      int ad=low&8?'a':'d';
      if (low==i-1) sprintf(add,"%c%d/",     ad,low&7);
      if (low< i-1) sprintf(add,"%c%d-%c%d/",ad,low&7, ad,(i-1)&7);
      strcat(list,add);

      low=i; // Next section
    }

    if (bit==0) low=i+1;
  }

  // Knock off trailing '/'
  len=strlen(list);
  if (len>0) if (list[len-1]=='/') list[len-1]=0; 
  return 0;
}