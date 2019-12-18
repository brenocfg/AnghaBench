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
 int* keyonce ; 
 scalar_t__* keys ; 

__attribute__((used)) static int _keyonly(int a)
{
 if(keys[a])
 {
  if(!keyonce[a]) 
  {
   keyonce[a]=1;
   return(1);
  }
 }
 else
  keyonce[a]=0;
 return(0);
}