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
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int /*<<< orphan*/ * Buffer ; 
 size_t BufferIn ; 
 size_t BufferSize ; 
 size_t BufferWrite ; 
 int /*<<< orphan*/  SDL_Delay (int) ; 

void WriteSound(int32 *buf, int Count)
{
 while(Count)
 {
  while(BufferIn == BufferSize) SDL_Delay(1);
  Buffer[BufferWrite] = *buf;
  Count--;
  BufferWrite = (BufferWrite + 1) % BufferSize;
  BufferIn++;
  buf++;
 }
}