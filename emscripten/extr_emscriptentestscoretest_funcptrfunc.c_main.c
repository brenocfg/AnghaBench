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
typedef  int /*<<< orphan*/  (* funcptrfunc ) (int) ;

/* Variables and functions */
 int /*<<< orphan*/  getIt (int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
  funcptrfunc fpf = argc < 100 ? getIt : NULL;
  printf("*%p*\n", fpf(argc));
  return 0;
}