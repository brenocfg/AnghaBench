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
 int /*<<< orphan*/  printf (char*,unsigned int,float,float,float) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned int*,float*,float*,float*) ; 

int main() {
  unsigned int a;
  float e, f, g;
  sscanf("a 1.1 1.1 1.1", "%X %E %F %G", &a, &e, &f, &g);
  printf("%d %.1F %.1F %.1F\n", a, e, f, g);
}