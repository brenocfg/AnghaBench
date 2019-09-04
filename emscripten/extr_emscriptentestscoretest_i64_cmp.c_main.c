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
 int compare (int) ; 
 int compare2 (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 

int main(int argc, char* argv[]) {
  printf("*%d,%d,%d,%d,%d,%d*\n", argc, compare(argc - 1 - 12),
         compare(1000 + argc), compare2(argc - 1 - 10), compare2(argc - 1 - 14),
         compare2(argc + 1000));
  return 0;
}