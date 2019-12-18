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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ int16 ;

/* Variables and functions */
 scalar_t__* Buffer ; 
 scalar_t__ BufferIn ; 
 size_t BufferRead ; 
 size_t BufferSize ; 

__attribute__((used)) static void fillaudio(void *udata, uint8 *stream, int len)
{
 int16 *tmps = (int16*)stream;
 len >>= 1;

 while(len)
 {
  int16 sample = 0;
  if(BufferIn)
  {
   sample = Buffer[BufferRead];
   BufferRead = (BufferRead + 1) % BufferSize;
   BufferIn--;
  }
  else sample = 0;

  *tmps = sample;
  tmps++;
  len--;
 }
}