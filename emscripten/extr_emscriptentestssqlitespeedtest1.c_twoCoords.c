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
 unsigned int speedtest1_random () ; 

__attribute__((used)) static void twoCoords(
  int p1, int p2,                   /* Parameters adjusting sizes */
  unsigned mx,                      /* Range of 1..mx */
  unsigned *pX0, unsigned *pX1      /* OUT: write results here */
){
  unsigned d, x0, x1, span;

  span = mx/100 + 1;
  if( speedtest1_random()%3==0 ) span *= p1;
  if( speedtest1_random()%p2==0 ) span = mx/2;
  d = speedtest1_random()%span + 1;
  x0 = speedtest1_random()%(mx-d) + 1;
  x1 = x0 + d;
  *pX0 = x0;
  *pX1 = x1;
}