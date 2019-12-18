#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kind; int siz; int idx; char const* s; } ;
typedef  TYPE_1__ Capture ;

/* Variables and functions */
 scalar_t__ Cclose ; 
 scalar_t__ Cruntime ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void adddyncaptures (const char *s, Capture *base, int n, int fd) {
  int i;
  assert(base[0].kind == Cruntime && base[0].siz == 0);
  base[0].idx = fd;  /* first returned capture */
  for (i = 1; i < n; i++) {  /* add extra captures */
    base[i].siz = 1;  /* mark it as closed */
    base[i].s = s;
    base[i].kind = Cruntime;
    base[i].idx = fd + i;  /* stack index */
  }
  base[n].kind = Cclose;  /* add closing entry */
  base[n].siz = 1;
  base[n].s = s;
}