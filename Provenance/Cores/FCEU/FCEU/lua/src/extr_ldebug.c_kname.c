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
struct TYPE_3__ {int /*<<< orphan*/ * k; } ;
typedef  TYPE_1__ Proto ;

/* Variables and functions */
 size_t INDEXK (int) ; 
 scalar_t__ ISK (int) ; 
 char const* svalue (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *kname (Proto *p, int c) {
  if (ISK(c) && ttisstring(&p->k[INDEXK(c)]))
    return svalue(&p->k[INDEXK(c)]);
  else
    return "?";
}