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
 int memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int strncasecmp (char*,char*,int) ; 
 int strncmp (char*,char*,int) ; 

int main() {
#define TEST(func)                                  \
  {                                                 \
    char *word = (char*)"WORD";                     \
    char wordEntry[2] = {-61, -126}; /* "Â"; */    \
    int cmp = func(word, wordEntry, 2);             \
    if (cmp < 0) cmp = -1;                          \
    else if (cmp > 0) cmp = 1;                      \
    printf("Compare value " #func " is %d\n", cmp); \
  }
  TEST(strncmp);
  TEST(strncasecmp);
  TEST(memcmp);
}