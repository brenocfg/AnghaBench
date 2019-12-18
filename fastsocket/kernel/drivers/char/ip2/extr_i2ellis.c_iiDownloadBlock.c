#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* loadHdrStrPtr ;
typedef  TYPE_5__* i2eBordStrPtr ;
struct TYPE_13__ {int porDiag2; } ;
struct TYPE_14__ {TYPE_2__ e; } ;
struct TYPE_16__ {scalar_t__ i2eValid; int i2eState; TYPE_3__ i2ePom; int /*<<< orphan*/  i2eData; scalar_t__ i2eToLoad; int /*<<< orphan*/  i2eLSub; int /*<<< orphan*/  i2eLRevision; int /*<<< orphan*/  i2eLVersion; } ;
struct TYPE_12__ {int /*<<< orphan*/  loadSubRevision; int /*<<< orphan*/  loadRevision; int /*<<< orphan*/  loadVersion; int /*<<< orphan*/  loadBlocksMore; int /*<<< orphan*/  loadMagic; } ;
struct TYPE_15__ {int /*<<< orphan*/  c; TYPE_1__ e; } ;

/* Variables and functions */
 scalar_t__ I2E_MAGIC ; 
 scalar_t__ I2_HAS_INPUT (TYPE_5__*) ; 
 int II_DOWN_BAD ; 
 int II_DOWN_BADFILE ; 
 int II_DOWN_BADSTATE ; 
 int II_DOWN_BADVALID ; 
 int II_DOWN_CONTINUING ; 
 int II_DOWN_GOOD ; 
 int II_DOWN_TIMEOUT ; 
 int II_STATE_BADLOAD ; 
 int II_STATE_LOADED ; 
#define  II_STATE_LOADING 131 
#define  II_STATE_READY 130 
 int II_STATE_STDLOADED ; 
#define  LOADWARE_BAD 129 
 int /*<<< orphan*/  LOADWARE_BLOCK_SIZE ; 
#define  LOADWARE_OK 128 
 int /*<<< orphan*/  MAGIC_LOADFILE ; 
 int MAX_DLOAD_ACK_TIME ; 
 int /*<<< orphan*/  MAX_DLOAD_READ_TIME ; 
 int /*<<< orphan*/  MAX_DLOAD_START_TIME ; 
 int POR_DEBUG_PORT ; 
 int /*<<< orphan*/  iiDelay (TYPE_5__*,int) ; 
 int /*<<< orphan*/  iiWaitForTxEmpty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iiWriteBuf (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iiDownloadBlock ( i2eBordStrPtr pB, loadHdrStrPtr pSource, int isStandard)
{
	int itemp;
	int loadedFirst;

	if (pB->i2eValid != I2E_MAGIC) return II_DOWN_BADVALID;

	switch(pB->i2eState)
	{
	case II_STATE_READY:

		// Loading the first block after reset. Must check the magic number of the
		// loadfile, store the number of blocks we expect to load.
		if (pSource->e.loadMagic != MAGIC_LOADFILE)
		{
			return II_DOWN_BADFILE;
		}

		// Next we store the total number of blocks to load, including this one.
		pB->i2eToLoad = 1 + pSource->e.loadBlocksMore;

		// Set the state, store the version numbers. ('Cause this may have come
		// from a file - we might want to report these versions and revisions in
		// case of an error!
		pB->i2eState = II_STATE_LOADING;
		pB->i2eLVersion = pSource->e.loadVersion;
		pB->i2eLRevision = pSource->e.loadRevision;
		pB->i2eLSub = pSource->e.loadSubRevision;

		// The time and date of compilation is also available but don't bother
		// storing it for normal purposes.
		loadedFirst = 1;
		break;

	case II_STATE_LOADING:
		loadedFirst = 0;
		break;

	default:
		return II_DOWN_BADSTATE;
	}

	// Now we must be in the II_STATE_LOADING state, and we assume i2eToLoad
	// must be positive still, because otherwise we would have cleaned up last
	// time and set the state to II_STATE_LOADED.
	if (!iiWaitForTxEmpty(pB, MAX_DLOAD_READ_TIME)) {
		return II_DOWN_TIMEOUT;
	}

	if (!iiWriteBuf(pB, pSource->c, LOADWARE_BLOCK_SIZE)) {
		return II_DOWN_BADVALID;
	}

	// If we just loaded the first block, wait for the fifo to empty an extra
	// long time to allow for any special startup code in the firmware, like
	// sending status messages to the LCD's.

	if (loadedFirst) {
		if (!iiWaitForTxEmpty(pB, MAX_DLOAD_START_TIME)) {
			return II_DOWN_TIMEOUT;
		}
	}

	// Determine whether this was our last block!
	if (--(pB->i2eToLoad)) {
		return II_DOWN_CONTINUING;    // more to come...
	}

	// It WAS our last block: Clean up operations...
	// ...Wait for last buffer to drain from the board...
	if (!iiWaitForTxEmpty(pB, MAX_DLOAD_READ_TIME)) {
		return II_DOWN_TIMEOUT;
	}
	// If there were only a single block written, this would come back
	// immediately and be harmless, though not strictly necessary.
	itemp = MAX_DLOAD_ACK_TIME/10;
	while (--itemp) {
		if (I2_HAS_INPUT(pB)) {
			switch (inb(pB->i2eData)) {
			case LOADWARE_OK:
				pB->i2eState =
					isStandard ? II_STATE_STDLOADED :II_STATE_LOADED;

				// Some revisions of the bootstrap firmware (e.g. ISA-8 1.0.2)
				// will, // if there is a debug port attached, require some
				// time to send information to the debug port now. It will do
				// this before // executing any of the code we just downloaded.
				// It may take up to 700 milliseconds.
				if (pB->i2ePom.e.porDiag2 & POR_DEBUG_PORT) {
					iiDelay(pB, 700);
				}

				return II_DOWN_GOOD;

			case LOADWARE_BAD:
			default:
				return II_DOWN_BAD;
			}
		}

		iiDelay(pB, 10);      // 10 mS granularity on checking condition
	}

	// Drop-through --> timed out waiting for firmware confirmation

	pB->i2eState = II_STATE_BADLOAD;
	return II_DOWN_TIMEOUT;
}