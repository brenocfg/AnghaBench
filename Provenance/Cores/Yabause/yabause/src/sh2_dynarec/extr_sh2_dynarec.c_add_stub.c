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
 size_t stubcount ; 
 int** stubs ; 

add_stub(int type,int addr,int retaddr,int a,int b,int c,int d,int e)
{
  stubs[stubcount][0]=type;
  stubs[stubcount][1]=addr;
  stubs[stubcount][2]=retaddr;
  stubs[stubcount][3]=a;
  stubs[stubcount][4]=b;
  stubs[stubcount][5]=c;
  stubs[stubcount][6]=d;
  stubs[stubcount][7]=e;
  stubcount++;
}