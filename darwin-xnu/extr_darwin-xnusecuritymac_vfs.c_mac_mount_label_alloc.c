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
 int /*<<< orphan*/  MAC_WAITOK ; 
 struct label* mac_labelzone_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_label_init ; 

__attribute__((used)) static struct label *
mac_mount_label_alloc(void)
{
	struct label *label;

	label = mac_labelzone_alloc(MAC_WAITOK);
	if (label == NULL)
		return (NULL);
	MAC_PERFORM(mount_label_init, label);
	return (label);
}