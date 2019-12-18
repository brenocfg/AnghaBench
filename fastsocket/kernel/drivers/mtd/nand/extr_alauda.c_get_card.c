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
typedef  scalar_t__ u8 ;
struct alauda_card {scalar_t__ id; } ;

/* Variables and functions */
 struct alauda_card* alauda_card_ids ; 

__attribute__((used)) static struct alauda_card *get_card(u8 id)
{
	struct alauda_card *card;

	for (card = alauda_card_ids; card->id; card++)
		if (card->id == id)
			return card;
	return NULL;
}