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
typedef  int /*<<< orphan*/  __llvm_profile_data ;
typedef  int /*<<< orphan*/  VPDataReaderType ;
typedef  int /*<<< orphan*/  ProfDataWriter ;
typedef  int /*<<< orphan*/  ProfBufferIO ;

/* Variables and functions */
 scalar_t__ lprofBufferIOFlush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lprofCreateBufferIO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lprofDeleteBufferIO (int /*<<< orphan*/ *) ; 
 scalar_t__ writeOneValueProfData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int writeValueProfData(ProfDataWriter *Writer,
                              VPDataReaderType *VPDataReader,
                              const __llvm_profile_data *DataBegin,
                              const __llvm_profile_data *DataEnd) {
  ProfBufferIO *BufferIO;
  const __llvm_profile_data *DI = 0;

  if (!VPDataReader)
    return 0;

  BufferIO = lprofCreateBufferIO(Writer);

  for (DI = DataBegin; DI < DataEnd; DI++) {
    if (writeOneValueProfData(BufferIO, VPDataReader, DI))
      return -1;
  }

  if (lprofBufferIOFlush(BufferIO) != 0)
    return -1;
  lprofDeleteBufferIO(BufferIO);

  return 0;
}