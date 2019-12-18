#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ code; } ;
struct TYPE_8__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 scalar_t__ IEnd ; 
 int /*<<< orphan*/  ischeck (TYPE_2__*) ; 
 int /*<<< orphan*/  isnofail (TYPE_2__*) ; 
 int /*<<< orphan*/  sizei (TYPE_2__*) ; 

__attribute__((used)) static int isheadfail (Instruction *p) {
  if (!ischeck(p)) return 0;
  /* check that other operations cannot fail */
  for (p += sizei(p); p->i.code != IEnd; p += sizei(p))
    if (!isnofail(p)) return 0;
  return 1;
}