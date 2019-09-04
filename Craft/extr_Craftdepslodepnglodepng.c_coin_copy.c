#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  symbols; int /*<<< orphan*/  weight; } ;
typedef  TYPE_1__ Coin ;

/* Variables and functions */
 int /*<<< orphan*/  uivector_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void coin_copy(Coin* c1, const Coin* c2)
{
  c1->weight = c2->weight;
  uivector_copy(&c1->symbols, &c2->symbols);
}