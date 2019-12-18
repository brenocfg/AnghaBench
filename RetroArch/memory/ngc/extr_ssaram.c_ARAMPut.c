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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARAMFetch (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  ARAM_WRITE ; 
 scalar_t__ AR_GetDMAStatus () ; 
 int /*<<< orphan*/  AR_StartDMA (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DCFlushRange (scalar_t__,int) ; 
 scalar_t__ aramfix ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 

void ARAMPut(char *src, char *dst, int len)
{
  u32 misalignaddress;
  u32 misalignedbytes;
  u32 misalignedbytestodo;

  int i, block;
  int offset = 0;

  /*** Check destination alignment ***/
  if ((u32) dst & 0x1f)
  {
    /*** Retrieve previous 32 byte section ***/
    misalignaddress = ((u32) dst & ~0x1f);
    misalignedbytestodo = 32 - ((u32) dst & 0x1f);
    misalignedbytes = ((u32) dst & 0x1f);
    ARAMFetch(aramfix, (char *) misalignaddress, 32);

    /*** Update from source ***/
    memcpy(aramfix + misalignedbytes, src, misalignedbytestodo);

    /*** Put it back ***/
    DCFlushRange(aramfix, 32);
    AR_StartDMA(ARAM_WRITE, (u32) aramfix, (u32) dst & ~0x1f, 32);
    while (AR_GetDMAStatus());

    /*** Update pointers ***/
    src += misalignedbytestodo;
    len -= misalignedbytestodo;
    dst = (char *) (((u32) dst & ~0x1f) + 32);
  }

  /*** Move 2k blocks - saves aligning source buffer ***/
  block = (len >> 11);
  for (i = 0; i < block; i++)
  {
    memcpy(aramfix, src + offset, 2048);
    DCFlushRange(aramfix, 2048);
    AR_StartDMA(ARAM_WRITE, (u32) aramfix, (u32) dst + offset, 2048);
    while (AR_GetDMAStatus());
    offset += 2048;
  }

  /*** Clean up remainder ***/
  len &= 0x7ff;
  if (len)
  {
    block = len & 0x1f;		/*** Is length aligned ? ***/
    memcpy(aramfix, src + offset, len & ~0x1f);
    DCFlushRange(aramfix, len & ~0x1f);
    AR_StartDMA(ARAM_WRITE, (u32) aramfix, (u32) dst + offset, len & ~0x1f);
    while (AR_GetDMAStatus());

    if (block)
    {
      offset += len & ~0x1f;
      misalignedbytes = len & 0x1f;

      /*** Do same shuffle as destination alignment ***/
      ARAMFetch(aramfix, dst + offset, 32);
      memcpy(aramfix, src + offset, misalignedbytes);
      DCFlushRange(aramfix, 32);
      AR_StartDMA(ARAM_WRITE, (u32) aramfix, (u32) dst + offset, 32);
      while (AR_GetDMAStatus());
    }
  }
}