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
struct TYPE_2__ {int page_size; } ;

/* Variables and functions */
 TYPE_1__ mparams ; 
 int page_align (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

int main() {
  mparams.page_size = 4096;
  printf("*%d,%d,%d,%d*\n", mparams.page_size, page_align(1000),
         page_align(6000), page_align(66474));
  return 0;
}