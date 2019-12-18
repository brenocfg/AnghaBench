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
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asd_init_cseq_mdp (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_init_cseq_mip (struct asd_ha_struct*) ; 

__attribute__((used)) static void asd_init_cseq_scratch(struct asd_ha_struct *asd_ha)
{
	asd_init_cseq_mip(asd_ha);
	asd_init_cseq_mdp(asd_ha);
}