#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  loadHdrStrPtr ;
typedef  TYPE_1__* i2eBordStrPtr ;
struct TYPE_4__ {scalar_t__ i2eState; } ;

/* Variables and functions */
 int II_DOWN_BADSTATE ; 
#define  II_DOWN_CONTINUING 129 
#define  II_DOWN_GOOD 128 
 int II_DOWN_OVER ; 
 int II_DOWN_UNDER ; 
 scalar_t__ II_STATE_READY ; 
 scalar_t__ LOADWARE_BLOCK_SIZE ; 
 int iiDownloadBlock (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iiDownloadAll(i2eBordStrPtr pB, loadHdrStrPtr pSource, int isStandard, int size)
{
	int status;

	// We know (from context) board should be ready for the first block of
	// download.  Complain if not.
	if (pB->i2eState != II_STATE_READY) return II_DOWN_BADSTATE;

	while (size > 0) {
		size -= LOADWARE_BLOCK_SIZE;	// How much data should there be left to
										// load after the following operation ?

		// Note we just bump pSource by "one", because its size is actually that
		// of an entire block, same as LOADWARE_BLOCK_SIZE.
		status = iiDownloadBlock(pB, pSource++, isStandard);

		switch(status)
		{
		case II_DOWN_GOOD:
			return ( (size > 0) ? II_DOWN_OVER : II_DOWN_GOOD);

		case II_DOWN_CONTINUING:
			break;

		default:
			return status;
		}
	}

	// We shouldn't drop out: it means "while" caught us with nothing left to
	// download, yet the previous DownloadBlock did not return complete. Ergo,
	// not enough data to match the size byte in the header.
	return II_DOWN_UNDER;
}