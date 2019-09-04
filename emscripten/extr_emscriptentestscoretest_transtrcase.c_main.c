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
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  strlwr (char*) ; 
 int /*<<< orphan*/  strupr (char*) ; 

int main() {
  char szToupr[] = "hello, ";
  char szTolwr[] = "EMSCRIPTEN";
  strupr(szToupr);
  strlwr(szTolwr);
  puts(szToupr);
  puts(szTolwr);
  return 0;
}