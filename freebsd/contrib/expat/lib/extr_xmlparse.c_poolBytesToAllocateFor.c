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
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK ; 
 size_t const INT_MAX ; 
 unsigned int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s ; 

__attribute__((used)) static size_t
poolBytesToAllocateFor(int blockSize)
{
  /* Unprotected math would be:
  ** return offsetof(BLOCK, s) + blockSize * sizeof(XML_Char);
  **
  ** Detect overflow, avoiding _signed_ overflow undefined behavior
  ** For a + b * c we check b * c in isolation first, so that addition of a
  ** on top has no chance of making us accept a small non-negative number
  */
  const size_t stretch = sizeof(XML_Char);  /* can be 4 bytes */

  if (blockSize <= 0)
    return 0;

  if (blockSize > (int)(INT_MAX / stretch))
    return 0;

  {
    const int stretchedBlockSize = blockSize * (int)stretch;
    const int bytesToAllocate = (int)(
        offsetof(BLOCK, s) + (unsigned)stretchedBlockSize);
    if (bytesToAllocate < 0)
      return 0;

    return (size_t)bytesToAllocate;
  }
}