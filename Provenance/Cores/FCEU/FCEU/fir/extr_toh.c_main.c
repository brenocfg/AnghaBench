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
 int MAX ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 int sscanf (char*,char*,double*) ; 
 int /*<<< orphan*/  stdin ; 

main()
{
 char buf[256];
 int count=0;

 while(fgets(buf,256,stdin)>0)
 {
  double p;

  if(sscanf(buf,"%lf",&p)==1)
  {
   p*=65536*16;
   printf("%ld,\n",(long)p);
   count++;
   if(count==MAX) break;
  }

 }

}