#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rio_info {int dummy; } ;
struct Map {int dummy; } ;
struct Host {TYPE_1__* Mapping; } ;
struct TYPE_2__ {int Flags; } ;

/* Variables and functions */
 int MAX_RUP ; 
 scalar_t__ RIOFreeDisconnected (struct rio_info*,struct Host*,int) ; 
 int /*<<< orphan*/  RIO_DEBUG_ROUTE ; 
 int RTA16_SECOND_SLOT ; 
 int SLOT_TENTATIVE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 

int RIOFindFreeID(struct rio_info *p, struct Host *HostP, unsigned int * pID1, unsigned int * pID2)
{
	int unit, tempID;

	/*
	 ** Initialise the ID's to MAX_RUP.
	 ** We do this to make the loop for setting the ID's as simple as
	 ** possible.
	 */
	*pID1 = MAX_RUP;
	if (pID2 != NULL)
		*pID2 = MAX_RUP;

	/*
	 ** Scan all entries of the host mapping table for free slots.
	 ** We scan for free slots first and then if that is not successful
	 ** we start all over again looking for tentative slots we can re-use.
	 */
	for (unit = 0; unit < MAX_RUP; unit++) {
		rio_dprintk(RIO_DEBUG_ROUTE, "Scanning unit %d\n", unit);
		/*
		 ** If the flags are zero then the slot is empty.
		 */
		if (HostP->Mapping[unit].Flags == 0) {
			rio_dprintk(RIO_DEBUG_ROUTE, "      This slot is empty.\n");
			/*
			 ** If we haven't allocated the first ID then do it now.
			 */
			if (*pID1 == MAX_RUP) {
				rio_dprintk(RIO_DEBUG_ROUTE, "Make tentative entry for first unit %d\n", unit);
				*pID1 = unit;

				/*
				 ** If the second ID is not needed then we can return
				 ** now.
				 */
				if (pID2 == NULL)
					return 0;
			} else {
				/*
				 ** Allocate the second slot and return.
				 */
				rio_dprintk(RIO_DEBUG_ROUTE, "Make tentative entry for second unit %d\n", unit);
				*pID2 = unit;
				return 0;
			}
		}
	}

	/*
	 ** If we manage to come out of the free slot loop then we
	 ** need to start all over again looking for tentative slots
	 ** that we can re-use.
	 */
	rio_dprintk(RIO_DEBUG_ROUTE, "Starting to scan for tentative slots\n");
	for (unit = 0; unit < MAX_RUP; unit++) {
		if (((HostP->Mapping[unit].Flags & SLOT_TENTATIVE) || (HostP->Mapping[unit].Flags == 0)) && !(HostP->Mapping[unit].Flags & RTA16_SECOND_SLOT)) {
			rio_dprintk(RIO_DEBUG_ROUTE, "    Slot %d looks promising.\n", unit);

			if (unit == *pID1) {
				rio_dprintk(RIO_DEBUG_ROUTE, "    No it isn't, its the 1st half\n");
				continue;
			}

			/*
			 ** Slot is Tentative or Empty, but not a tentative second
			 ** slot of a 16 porter.
			 ** Attempt to free up this slot (and its parnter if
			 ** it is a 16 port slot. The second slot will become
			 ** empty after a call to RIOFreeDisconnected so thats why
			 ** we look for empty slots above  as well).
			 */
			if (HostP->Mapping[unit].Flags != 0)
				if (RIOFreeDisconnected(p, HostP, unit) != 0)
					continue;
			/*
			 ** If we haven't allocated the first ID then do it now.
			 */
			if (*pID1 == MAX_RUP) {
				rio_dprintk(RIO_DEBUG_ROUTE, "Grab tentative entry for first unit %d\n", unit);
				*pID1 = unit;

				/*
				 ** Clear out this slot now that we intend to use it.
				 */
				memset(&HostP->Mapping[unit], 0, sizeof(struct Map));

				/*
				 ** If the second ID is not needed then we can return
				 ** now.
				 */
				if (pID2 == NULL)
					return 0;
			} else {
				/*
				 ** Allocate the second slot and return.
				 */
				rio_dprintk(RIO_DEBUG_ROUTE, "Grab tentative/empty  entry for second unit %d\n", unit);
				*pID2 = unit;

				/*
				 ** Clear out this slot now that we intend to use it.
				 */
				memset(&HostP->Mapping[unit], 0, sizeof(struct Map));

				/* At this point under the right(wrong?) conditions
				 ** we may have a first unit ID being higher than the
				 ** second unit ID. This is a bad idea if we are about
				 ** to fill the slots with a 16 port RTA.
				 ** Better check and swap them over.
				 */

				if (*pID1 > *pID2) {
					rio_dprintk(RIO_DEBUG_ROUTE, "Swapping IDS %d %d\n", *pID1, *pID2);
					tempID = *pID1;
					*pID1 = *pID2;
					*pID2 = tempID;
				}
				return 0;
			}
		}
	}

	/*
	 ** If we manage to get to the end of the second loop then we
	 ** can give up and return a failure.
	 */
	return 1;
}