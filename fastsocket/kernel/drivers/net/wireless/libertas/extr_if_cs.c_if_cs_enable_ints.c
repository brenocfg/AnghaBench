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
struct if_cs_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_CS_HOST_INT_MASK ; 
 int /*<<< orphan*/  LBS_DEB_CS ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void if_cs_enable_ints(struct if_cs_card *card)
{
	lbs_deb_enter(LBS_DEB_CS);
	if_cs_write16(card, IF_CS_HOST_INT_MASK, 0);
}