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
struct display {unsigned int size; int /*<<< orphan*/  min_windowBits; } ;
struct TYPE_2__ {scalar_t__ name; int value; } ;

/* Variables and functions */
 int MAX_WBITS ; 
 int /*<<< orphan*/  OPTIND (struct display*,int /*<<< orphan*/ ) ; 
 TYPE_1__* VLNAME (int /*<<< orphan*/ ) ; 
 int VLSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ range_hi ; 
 scalar_t__ range_lo ; 
 int /*<<< orphan*/  windowBits ; 
 int /*<<< orphan*/  windowBits_IDAT ; 

__attribute__((used)) static void
set_windowBits_hi(struct display *dp)
{
   /* windowBits is in the range 8..15 but zlib maps '8' to '9' so it is only
    * worth using if the data size is 256 byte or less.
    */
   int wb = MAX_WBITS; /* for large images */
   int i = VLSIZE(windowBits_IDAT);

   while (wb > 8 && dp->size <= 1U<<(wb-1)) --wb;

   while (--i >= 0) if (VLNAME(windowBits_IDAT)[i].name == range_hi) break;

   assert(i > 1); /* vl_windowBits_IDAT always has a RANGE() */
   VLNAME(windowBits_IDAT)[i].value = wb;

   assert(VLNAME(windowBits_IDAT)[--i].name == range_lo);
   VLNAME(windowBits_IDAT)[i].value = wb > 8 ? 9 : 8;

   /* If wb == 8 then any search has been restricted to just one windowBits
    * entry.  Record that here to avoid producing a spurious app-level warning
    * above.
    */
   if (wb == 8)
      dp->min_windowBits = OPTIND(dp, windowBits);
}