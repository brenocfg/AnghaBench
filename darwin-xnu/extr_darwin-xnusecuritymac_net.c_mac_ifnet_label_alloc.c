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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ifnet_label_init ; 
 struct label* mac_labelzone_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct label *
mac_ifnet_label_alloc(void)
{
	struct label *label;

	label = mac_labelzone_alloc(M_WAITOK);
	if (label == NULL)
		return (NULL);
	MAC_PERFORM(ifnet_label_init, label);
	return (label);
}