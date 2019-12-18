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
struct carlfw {int dummy; } ;
struct carl9170fw_desc_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  carlfw_desc_to_entry (struct carl9170fw_desc_head*) ; 
 int /*<<< orphan*/  carlfw_entry_del (struct carlfw*,int /*<<< orphan*/ ) ; 

void carlfw_desc_del(struct carlfw *fw,
	struct carl9170fw_desc_head *desc)
{
	carlfw_entry_del(fw, carlfw_desc_to_entry(desc));
}