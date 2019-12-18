#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {int ElmSize; int NumElm; scalar_t__ Data; } ;
struct TYPE_5__ {scalar_t__ WriterCtx; } ;
typedef  TYPE_1__ ProfDataWriter ;
typedef  TYPE_2__ ProfDataIOVec ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fwrite (scalar_t__,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t fileWriter(ProfDataWriter *This, ProfDataIOVec *IOVecs,
                           uint32_t NumIOVecs) {
  uint32_t I;
  FILE *File = (FILE *)This->WriterCtx;
  for (I = 0; I < NumIOVecs; I++) {
    if (IOVecs[I].Data) {
      if (fwrite(IOVecs[I].Data, IOVecs[I].ElmSize, IOVecs[I].NumElm, File) !=
          IOVecs[I].NumElm)
        return 1;
    } else {
      if (fseek(File, IOVecs[I].ElmSize * IOVecs[I].NumElm, SEEK_CUR) == -1)
        return 1;
    }
  }
  return 0;
}