#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float f; float d; } ;

/* Variables and functions */
 double XXXd ; 
 double XXXf ; 
 int /*<<< orphan*/  printf (char*,float) ; 
 TYPE_1__* xx ; 

int main(int argc, char ** argv) {
  float YYYf = -0.0f;
  float YYYd = -0.0;

  printf("%.2f\n", XXXf);
  printf("%.2f\n", XXXd);
  printf("%.2f\n", YYYf);
  printf("%.2f\n", YYYd);
  printf("%.2f\n", xx->f);
  printf("%.2f\n", xx->d);
}