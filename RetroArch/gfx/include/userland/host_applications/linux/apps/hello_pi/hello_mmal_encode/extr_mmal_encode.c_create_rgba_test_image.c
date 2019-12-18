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
typedef  int uint32_t ;

/* Variables and functions */
 int ALPHA ; 
 int BLUE ; 
 unsigned int BYTESPP ; 
 int GREEN ; 
 int RED ; 
 int WIDTH ; 

void create_rgba_test_image(void* buf, unsigned int length, unsigned int stride)
{
   uint32_t* pixel = buf;
   int i;
   for (i=0; i<length/BYTESPP; ++i) {
      switch ((i % stride) / (WIDTH / 8)) {
      case 0: *pixel = RED | GREEN | BLUE; break;
      case 1: *pixel = 0; break;
      case 2: *pixel = RED; break;
      case 3: *pixel = GREEN; break;
      case 4: *pixel = BLUE; break;
      case 5: *pixel = GREEN | BLUE; break;
      case 6: *pixel = RED | BLUE; break;
      case 7: *pixel = RED | GREEN; break;
      }
      *pixel |= ALPHA; // Full alpha
      ++pixel;
   }
}