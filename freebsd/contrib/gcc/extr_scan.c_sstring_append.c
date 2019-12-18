#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ptr; char* base; } ;
typedef  TYPE_1__ sstring ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_SSTRING_SPACE (TYPE_1__*,int) ; 
 int SSTRING_LENGTH (TYPE_1__*) ; 

void
sstring_append (sstring *dst, sstring *src)
{
  char *d, *s;
  int count = SSTRING_LENGTH (src);

  MAKE_SSTRING_SPACE (dst, count + 1);
  d = dst->ptr;
  s = src->base;
  while (--count >= 0) *d++ = *s++;
  dst->ptr = d;
  *d = 0;
}