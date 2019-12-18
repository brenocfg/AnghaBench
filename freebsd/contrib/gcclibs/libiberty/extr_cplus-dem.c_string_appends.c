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
struct TYPE_5__ {scalar_t__ b; scalar_t__ p; } ;
typedef  TYPE_1__ string ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,int,int) ; 
 int /*<<< orphan*/  string_need (TYPE_1__*,int) ; 

__attribute__((used)) static void
string_appends (string *p, string *s)
{
  int n;

  if (s->b != s->p)
    {
      n = s->p - s->b;
      string_need (p, n);
      memcpy (p->p, s->b, n);
      p->p += n;
    }
}