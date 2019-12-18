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

/* Variables and functions */
 char ONE_STAGE_COMP ; 
 char TWO_STAGE_COMP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int tsDecompressFloatImp (char* const,int const,char* const) ; 
 int /*<<< orphan*/  tsDecompressStringImp (char const* const,int,char* const,int) ; 

int tsDecompressFloat(const char *const input, int compressedSize, const int nelements, char *const output,
                      int outputSize, char algorithm, char *const buffer, int bufferSize) {
  if (algorithm == ONE_STAGE_COMP) {
    return tsDecompressFloatImp(input, nelements, output);
  } else if (algorithm == TWO_STAGE_COMP) {
    tsDecompressStringImp(input, compressedSize, buffer, bufferSize);
    return tsDecompressFloatImp(buffer, nelements, output);
  } else {
    assert(0);
  }
}