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
typedef  int /*<<< orphan*/  Charset ;

/* Variables and functions */
 int UCHAR_MAX ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ testchar (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void printcharset (const Charset st) {
  int i;
  printf("[");
  for (i = 0; i <= UCHAR_MAX; i++) {
    int first = i;
    while (testchar(st, i) && i <= UCHAR_MAX) i++;
    if (i - 1 == first)  /* unary range? */
      printf("(%02x)", first);
    else if (i - 1 > first)  /* non-empty range? */
      printf("(%02x-%02x)", first, i - 1);
  }
  printf("]");
}