#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int current; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int UCHAR_MAX ; 
 int /*<<< orphan*/  escerror (TYPE_1__*,int*,int,char*) ; 
 scalar_t__ lisdigit (int) ; 
 int /*<<< orphan*/  next (TYPE_1__*) ; 

__attribute__((used)) static int readdecesc (LexState *ls) {
  int c[3], i;
  int r = 0;  /* result accumulator */
  for (i = 0; i < 3 && lisdigit(ls->current); i++) {  /* read up to 3 digits */
    c[i] = ls->current;
    r = 10*r + c[i] - '0';
    next(ls);
  }
  if (r > UCHAR_MAX)
    escerror(ls, c, i, "decimal escape too large");
  return r;
}