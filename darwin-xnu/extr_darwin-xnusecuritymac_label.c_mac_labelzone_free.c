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
struct label {int l_flags; } ;

/* Variables and functions */
 int MAC_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  bzero (struct label*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  zone_label ; 

void
mac_labelzone_free(struct label *l)
{

	if (l == NULL)
		panic("Free of NULL MAC label\n");

	if ((l->l_flags & MAC_FLAG_INITIALIZED) == 0)
		panic("Free of uninitialized label\n");
	bzero(l, sizeof(struct label));
	zfree(zone_label, l);
}