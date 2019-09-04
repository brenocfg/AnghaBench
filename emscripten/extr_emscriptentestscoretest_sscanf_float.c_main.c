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
 int /*<<< orphan*/  printf (char*,float,float,float,float,float,float,float,float,float) ; 
 int /*<<< orphan*/  sscanf (char*,char*,float*,float*,float*,float*,float*,float*,float*,float*,float*) ; 

int main() {
  float f1, f2, f3, f4, f5, f6, f7, f8, f9;
  sscanf("0.512 0.250x5.129_-9.98 1.12*+54.32E3 +54.32E3^87.5E-3 87.5E-3$",
         "%f %fx%f_%f %f*%f %f^%f %f$", &f1, &f2, &f3, &f4, &f5, &f6, &f7, &f8,
         &f9);
  printf("\n%f, %f, %f, %f, %f, %f, %f, %f, %f\n", f1, f2, f3, f4, f5, f6, f7,
         f8, f9);
}