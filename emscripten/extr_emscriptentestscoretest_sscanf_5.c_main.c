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
 int /*<<< orphan*/ * colors ; 
 int /*<<< orphan*/  printf (char*,int,unsigned char,char*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned char*,char*) ; 

int main() {
  unsigned char code;
  char color[32];
  int rcode;
  for (int i = 0; i < 3; i++) {
    rcode = sscanf(colors[i], "%c c %s", &code, color);
    printf("%i, %c, %s\n", rcode, code, color);
  }
}