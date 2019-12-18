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
 int tsCompressStringImp (char const* const,int,char* const,int) ; 

int tsCompressString(const char *const input, int inputSize, const int nelements, char *const output, int outputSize,
                     char algorithm, char *const buffer, int bufferSize) {
  return tsCompressStringImp(input, inputSize, output, outputSize);
}