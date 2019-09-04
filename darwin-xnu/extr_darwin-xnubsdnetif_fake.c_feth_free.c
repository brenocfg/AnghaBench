#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_fake_ref ;
struct TYPE_5__ {scalar_t__ iff_retain_count; int /*<<< orphan*/  iff_name; scalar_t__ iff_pending_tx_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  FETH_DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  feth_cloner ; 
 scalar_t__ feth_in_bsd_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  if_clone_softc_deallocate (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  m_freem (scalar_t__) ; 

__attribute__((used)) static void
feth_free(if_fake_ref fakeif)
{
	assert(fakeif->iff_retain_count == 0);
	if (feth_in_bsd_mode(fakeif)) {
		if (fakeif->iff_pending_tx_packet) {
			m_freem(fakeif->iff_pending_tx_packet);
		}
	}

	FETH_DPRINTF("%s\n", fakeif->iff_name);
	if_clone_softc_deallocate(&feth_cloner, fakeif);
}