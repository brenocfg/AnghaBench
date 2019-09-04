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
 int /*<<< orphan*/  printf (char*,int) ; 
 char const* strstr (char const*,char*) ; 

int main() {
  printf("%d\n", !!strstr("\\n", "\\n"));
  printf("%d\n", !!strstr("cheezy", "ez"));
  printf("%d\n", !!strstr("cheeezy", "ez"));
  printf("%d\n", !!strstr("cheeeeeeeeeezy", "ez"));
  printf("%d\n", !!strstr("cheeeeeeeeee1zy", "ez"));
  printf("%d\n", !!strstr("che1ezy", "ez"));
  printf("%d\n", !!strstr("che1ezy", "che"));
  printf("%d\n", !!strstr("ce1ezy", "che"));
  printf("%d\n", !!strstr("ce1ezy", "ezy"));
  printf("%d\n", !!strstr("ce1ezyt", "ezy"));
  printf("%d\n", !!strstr("ce1ez1y", "ezy"));
  printf("%d\n", !!strstr("cheezy", "a"));
  printf("%d\n", !!strstr("cheezy", "b"));
  printf("%d\n", !!strstr("cheezy", "c"));
  printf("%d\n", !!strstr("cheezy", "d"));
  printf("%d\n", !!strstr("cheezy", "g"));
  printf("%d\n", !!strstr("cheezy", "h"));
  printf("%d\n", !!strstr("cheezy", "i"));
  printf("%d\n", !!strstr("cheezy", "e"));
  printf("%d\n", !!strstr("cheezy", "x"));
  printf("%d\n", !!strstr("cheezy", "y"));
  printf("%d\n", !!strstr("cheezy", "z"));
  printf("%d\n", !!strstr("cheezy", "_"));

  const char *str = "a big string";
  printf("%d\n", strstr(str, "big") - str);
  return 0;
}