#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int NumFolders; int /*<<< orphan*/  PackSizes; TYPE_1__* Folders; } ;
struct TYPE_10__ {scalar_t__ UnpackCRC; scalar_t__ UnpackCRCDefined; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  ILookInStream ;
typedef  TYPE_1__ CSzFolder ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  TYPE_2__ CSzAr ;
typedef  TYPE_3__ CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Create (TYPE_3__*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ CrcCalc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LookInStream_SeekTo (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_ARCHIVE ; 
 int /*<<< orphan*/  SZ_ERROR_CRC ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SzFolder_Decode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ SzFolder_GetUnpackSize (TYPE_1__*) ; 
 int /*<<< orphan*/  SzReadStreamsInfo (int /*<<< orphan*/ *,scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SRes SzReadAndDecodePackedStreams2(
      ILookInStream *inStream,
      CSzData *sd,
      CBuf *outBuffer,
      uint64_t baseOffset,
      CSzAr *p,
      uint64_t **unpackSizes,
      uint8_t **digestsDefined,
      uint32_t **digests,
      ISzAlloc *allocTemp)
{

   uint32_t numUnpackStreams = 0;
   uint64_t dataStartPos;
   CSzFolder *folder;
   uint64_t unpackSize;
   SRes res;

   RINOK(SzReadStreamsInfo(sd, &dataStartPos, p,
            &numUnpackStreams,  unpackSizes, digestsDefined, digests,
            allocTemp, allocTemp));

   dataStartPos += baseOffset;
   if (p->NumFolders != 1)
      return SZ_ERROR_ARCHIVE;

   folder = p->Folders;
   unpackSize = SzFolder_GetUnpackSize(folder);

   RINOK(LookInStream_SeekTo(inStream, dataStartPos));

   if (!Buf_Create(outBuffer, (size_t)unpackSize, allocTemp))
      return SZ_ERROR_MEM;

   res = SzFolder_Decode(folder, p->PackSizes,
         inStream, dataStartPos,
         outBuffer->data, (size_t)unpackSize, allocTemp);
   RINOK(res);
   if (folder->UnpackCRCDefined)
      if (CrcCalc(outBuffer->data, (size_t)unpackSize) != folder->UnpackCRC)
         return SZ_ERROR_CRC;
   return SZ_OK;
}