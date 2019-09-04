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
struct S {char* match_start; char* strstart; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,unsigned short,unsigned short,...) ; 

int main() {
  struct S _s;
  struct S *s = &_s;
  unsigned short int sh;

  s->match_start = (char *)32522;
  s->strstart = (char *)(32780);
  printf("*%d,%d,%d*\n", (int)s->strstart, (int)s->match_start,
         (int)(s->strstart - s->match_start));
  sh = s->strstart - s->match_start;
  printf("*%d,%d*\n", sh, sh >> 7);

  s->match_start = (char *)32999;
  s->strstart = (char *)(32780);
  printf("*%d,%d,%d*\n", (int)s->strstart, (int)s->match_start,
         (int)(s->strstart - s->match_start));
  sh = s->strstart - s->match_start;
  printf("*%d,%d*\n", sh, sh >> 7);
}