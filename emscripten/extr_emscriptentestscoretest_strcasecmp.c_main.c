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
 int /*<<< orphan*/  printf (char*,...) ; 
 int sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 

int main() {
  printf("*\n");

  printf("%d\n", sign(strcasecmp("hello", "hello")));
  printf("%d\n", sign(strcasecmp("hello1", "hello")));
  printf("%d\n", sign(strcasecmp("hello", "hello1")));
  printf("%d\n", sign(strcasecmp("hello1", "hello1")));
  printf("%d\n", sign(strcasecmp("iello", "hello")));
  printf("%d\n", sign(strcasecmp("hello", "iello")));
  printf("%d\n", sign(strcasecmp("A", "hello")));
  printf("%d\n", sign(strcasecmp("Z", "hello")));
  printf("%d\n", sign(strcasecmp("a", "hello")));
  printf("%d\n", sign(strcasecmp("z", "hello")));
  printf("%d\n", sign(strcasecmp("hello", "a")));
  printf("%d\n", sign(strcasecmp("hello", "z")));

  printf("%d\n", sign(strcasecmp("Hello", "hello")));
  printf("%d\n", sign(strcasecmp("Hello1", "hello")));
  printf("%d\n", sign(strcasecmp("Hello", "hello1")));
  printf("%d\n", sign(strcasecmp("Hello1", "hello1")));
  printf("%d\n", sign(strcasecmp("Iello", "hello")));
  printf("%d\n", sign(strcasecmp("Hello", "iello")));
  printf("%d\n", sign(strcasecmp("A", "hello")));
  printf("%d\n", sign(strcasecmp("Z", "hello")));
  printf("%d\n", sign(strcasecmp("a", "hello")));
  printf("%d\n", sign(strcasecmp("z", "hello")));
  printf("%d\n", sign(strcasecmp("Hello", "a")));
  printf("%d\n", sign(strcasecmp("Hello", "z")));

  printf("%d\n", sign(strcasecmp("hello", "Hello")));
  printf("%d\n", sign(strcasecmp("hello1", "Hello")));
  printf("%d\n", sign(strcasecmp("hello", "Hello1")));
  printf("%d\n", sign(strcasecmp("hello1", "Hello1")));
  printf("%d\n", sign(strcasecmp("iello", "Hello")));
  printf("%d\n", sign(strcasecmp("hello", "Iello")));
  printf("%d\n", sign(strcasecmp("A", "Hello")));
  printf("%d\n", sign(strcasecmp("Z", "Hello")));
  printf("%d\n", sign(strcasecmp("a", "Hello")));
  printf("%d\n", sign(strcasecmp("z", "Hello")));
  printf("%d\n", sign(strcasecmp("hello", "a")));
  printf("%d\n", sign(strcasecmp("hello", "z")));

  printf("%d\n", sign(strcasecmp("Hello", "Hello")));
  printf("%d\n", sign(strcasecmp("Hello1", "Hello")));
  printf("%d\n", sign(strcasecmp("Hello", "Hello1")));
  printf("%d\n", sign(strcasecmp("Hello1", "Hello1")));
  printf("%d\n", sign(strcasecmp("Iello", "Hello")));
  printf("%d\n", sign(strcasecmp("Hello", "Iello")));
  printf("%d\n", sign(strcasecmp("A", "Hello")));
  printf("%d\n", sign(strcasecmp("Z", "Hello")));
  printf("%d\n", sign(strcasecmp("a", "Hello")));
  printf("%d\n", sign(strcasecmp("z", "Hello")));
  printf("%d\n", sign(strcasecmp("Hello", "a")));
  printf("%d\n", sign(strcasecmp("Hello", "z")));

  printf("%d\n", sign(strncasecmp("hello", "hello", 3)));
  printf("%d\n", sign(strncasecmp("hello1", "hello", 3)));
  printf("%d\n", sign(strncasecmp("hello", "hello1", 3)));
  printf("%d\n", sign(strncasecmp("hello1", "hello1", 3)));
  printf("%d\n", sign(strncasecmp("iello", "hello", 3)));
  printf("%d\n", sign(strncasecmp("hello", "iello", 3)));
  printf("%d\n", sign(strncasecmp("A", "hello", 3)));
  printf("%d\n", sign(strncasecmp("Z", "hello", 3)));
  printf("%d\n", sign(strncasecmp("a", "hello", 3)));
  printf("%d\n", sign(strncasecmp("z", "hello", 3)));
  printf("%d\n", sign(strncasecmp("hello", "a", 3)));
  printf("%d\n", sign(strncasecmp("hello", "z", 3)));

  printf("*\n");

  return 0;
}