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
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  printf (char*,char,char,char,char,char*) ; 

int main() {
  char *c = "μ†ℱ ╋ℯ╳╋ 😇";
  printf("%d %d %d %d %s\n", c[0] & 0xff, c[1] & 0xff, c[2] & 0xff, c[3] & 0xff,
         c);
  emscripten_run_script(
      "cheez = _malloc(100);"
      "Module.stringToUTF8(\"μ†ℱ ╋ℯ╳╋ 😇\", cheez, 100);"
      "out([UTF8ToString(cheez), Module.getValue(cheez, "
      "'i8')&0xff, Module.getValue(cheez+1, 'i8')&0xff, "
      "Module.getValue(cheez+2, 'i8')&0xff, Module.getValue(cheez+3, "
      "'i8')&0xff].join(','));");
}