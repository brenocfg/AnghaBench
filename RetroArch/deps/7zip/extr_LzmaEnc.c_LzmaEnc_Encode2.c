#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  rc; int /*<<< orphan*/  nowPos64; scalar_t__ finished; } ;
struct TYPE_8__ {scalar_t__ (* Progress ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ ICompressProgress ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 scalar_t__ LzmaEnc_CodeOneBlock (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LzmaEnc_Finish (TYPE_2__*) ; 
 int /*<<< orphan*/  RangeEnc_GetProcessed (int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_ERROR_PROGRESS ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes LzmaEnc_Encode2(CLzmaEnc *p, ICompressProgress *progress)
{
  SRes res = SZ_OK;

  #ifndef _7ZIP_ST
  unsigned char allocaDummy[0x300];
  allocaDummy[0] = 0;
  allocaDummy[1] = allocaDummy[0];
  #endif

  for (;;)
  {
    res = LzmaEnc_CodeOneBlock(p, false, 0, 0);
    if (res != SZ_OK || p->finished)
      break;
    if (progress)
    {
      res = progress->Progress(progress, p->nowPos64, RangeEnc_GetProcessed(&p->rc));
      if (res != SZ_OK)
      {
        res = SZ_ERROR_PROGRESS;
        break;
      }
    }
  }

  LzmaEnc_Finish(p);

  return res;
}