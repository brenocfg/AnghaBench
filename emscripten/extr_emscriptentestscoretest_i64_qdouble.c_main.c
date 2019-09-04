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
typedef  int qreal ;
typedef  int qint64 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char **argv) {
  qreal c = 111;
  qint64 d = -111 + (argc - 1);
  c += d;
  if (c < -1 || c > 1) {
    printf("Failed!\n");
  } else {
    printf("Succeeded!\n");
  }
}