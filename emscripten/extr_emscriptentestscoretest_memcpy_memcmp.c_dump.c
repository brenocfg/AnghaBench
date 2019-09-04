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
 int MAXX ; 
 int /*<<< orphan*/  printf (char*,unsigned char) ; 

void dump(unsigned char *buffer) {
  for (int i = 0; i < MAXX - 1; i++) printf("%2d,", buffer[i]);
  printf("%d\n", buffer[MAXX - 1]);
}