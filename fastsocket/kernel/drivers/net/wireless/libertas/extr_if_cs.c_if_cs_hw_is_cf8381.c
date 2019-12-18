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
struct pcmcia_device {scalar_t__ manf_id; scalar_t__ card_id; } ;

/* Variables and functions */
 scalar_t__ CF8381_CARDID ; 
 scalar_t__ CF8381_MANFID ; 

__attribute__((used)) static inline int if_cs_hw_is_cf8381(struct pcmcia_device *p_dev)
{
	return (p_dev->manf_id == CF8381_MANFID &&
		p_dev->card_id == CF8381_CARDID);
}