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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main() {
  FILE* f1 = fopen("s", "r");
  if (f1 == NULL) {
    printf("file 's' not found!\n");
  }

  FILE* f2 = fopen("", "r");
  if (f2 == NULL) {
    printf("file '' not found!\n");
  }
  return 0;
}