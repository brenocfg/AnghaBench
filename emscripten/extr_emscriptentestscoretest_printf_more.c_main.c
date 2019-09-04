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
 int /*<<< orphan*/  asprintf (char**,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int snprintf (char*,int,char*,char*,int,double) ; 

int main() {
  int size = snprintf(NULL, 0, "%s %d %.2f\n", "me and myself", 25, 1.345);
  char buf[size];
  snprintf(buf, size, "%s %d %.2f\n", "me and myself", 25, 1.345);
  printf("%d : %s\n", size, buf);
  char *buff = NULL;
  asprintf(&buff, "%d waka %d\n", 21, 95);
  puts(buff);
  // test buffering, write more than a musl buffer at once
  #define X 1026
  char c[X];
  for(int i=0;i<X;i++) c[i] ='A';
  c[X-1] = '\0';
  printf("%s\n", c);  /// if X > 1025 this line doesn't print if we don't handle buffering properly
  return 0;
}