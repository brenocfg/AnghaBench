#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* bch; } ;
typedef  TYPE_2__ act2000_card ;
typedef  scalar_t__ __u16 ;
struct TYPE_4__ {scalar_t__ plci; } ;

/* Variables and functions */
 int ACT2000_BCH ; 

__attribute__((used)) static int
find_plci(act2000_card *card, __u16 plci)
{
	int i;
	for (i = 0; i < ACT2000_BCH; i++)
		if (card->bch[i].plci == plci)
			return i;
	return -1;
}