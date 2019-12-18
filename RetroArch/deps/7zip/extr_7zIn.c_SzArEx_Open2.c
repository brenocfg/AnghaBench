#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
struct TYPE_24__ {scalar_t__* data; int /*<<< orphan*/  size; } ;
struct TYPE_23__ {int startPosAfterHeader; } ;
struct TYPE_22__ {scalar_t__* Data; int /*<<< orphan*/  Size; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* Seek ) (TYPE_1__*,int*,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ ILookInStream ;
typedef  TYPE_2__ CSzData ;
typedef  TYPE_3__ CSzArEx ;
typedef  TYPE_4__ CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Create (TYPE_4__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Buf_Free (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Buf_Init (TYPE_4__*) ; 
 scalar_t__ CrcCalc (scalar_t__*,size_t) ; 
 scalar_t__ GetUi32 (scalar_t__*) ; 
 size_t GetUi64 (scalar_t__*) ; 
 scalar_t__ LookInStream_Read (TYPE_1__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  LookInStream_Read2 (TYPE_1__*,scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  LookInStream_SeekTo (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 scalar_t__ SZ_ERROR_ARCHIVE ; 
 scalar_t__ SZ_ERROR_CRC ; 
 scalar_t__ SZ_ERROR_INPUT_EOF ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_ERROR_NO_ARCHIVE ; 
 scalar_t__ SZ_ERROR_UNSUPPORTED ; 
 scalar_t__ SZ_OK ; 
 int /*<<< orphan*/  SZ_SEEK_CUR ; 
 int /*<<< orphan*/  SZ_SEEK_END ; 
 scalar_t__ SzReadAndDecodePackedStreams (TYPE_1__*,TYPE_2__*,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ SzReadHeader (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SzReadID (TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  TestSignatureCandidate (scalar_t__*) ; 
 size_t k7zIdEncodedHeader ; 
 size_t k7zIdHeader ; 
 scalar_t__ k7zMajorVersion ; 
 int k7zStartHeaderSize ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes SzArEx_Open2(
      CSzArEx *p,
      ILookInStream *inStream,
      ISzAlloc *allocMain,
      ISzAlloc *allocTemp)
{
   uint8_t header[k7zStartHeaderSize];
   int64_t startArcPos;
   uint64_t nextHeaderOffset, nextHeaderSize;
   size_t nextHeaderSizeT;
   uint32_t nextHeaderCRC;
   CBuf buffer;
   SRes res;

   startArcPos = 0;
   RINOK(inStream->Seek(inStream, &startArcPos, SZ_SEEK_CUR));

   RINOK(LookInStream_Read2(inStream, header, k7zStartHeaderSize, SZ_ERROR_NO_ARCHIVE));

   if (!TestSignatureCandidate(header))
      return SZ_ERROR_NO_ARCHIVE;
   if (header[6] != k7zMajorVersion)
      return SZ_ERROR_UNSUPPORTED;

   nextHeaderOffset = GetUi64(header + 12);
   nextHeaderSize = GetUi64(header + 20);
   nextHeaderCRC = GetUi32(header + 28);

   p->startPosAfterHeader = startArcPos + k7zStartHeaderSize;

   if (CrcCalc(header + 12, 20) != GetUi32(header + 8))
      return SZ_ERROR_CRC;

   nextHeaderSizeT = (size_t)nextHeaderSize;
   if (nextHeaderSizeT != nextHeaderSize)
      return SZ_ERROR_MEM;
   if (nextHeaderSizeT == 0)
      return SZ_OK;
   if (nextHeaderOffset > nextHeaderOffset + nextHeaderSize ||
         nextHeaderOffset > nextHeaderOffset + nextHeaderSize + k7zStartHeaderSize)
      return SZ_ERROR_NO_ARCHIVE;

   {
      int64_t pos = 0;
      RINOK(inStream->Seek(inStream, &pos, SZ_SEEK_END));
      if ((uint64_t)pos < startArcPos + nextHeaderOffset ||
            (uint64_t)pos < startArcPos + k7zStartHeaderSize + nextHeaderOffset ||
            (uint64_t)pos < startArcPos + k7zStartHeaderSize + nextHeaderOffset + nextHeaderSize)
         return SZ_ERROR_INPUT_EOF;
   }

   RINOK(LookInStream_SeekTo(inStream, startArcPos + k7zStartHeaderSize + nextHeaderOffset));

   if (!Buf_Create(&buffer, nextHeaderSizeT, allocTemp))
      return SZ_ERROR_MEM;

   res = LookInStream_Read(inStream, buffer.data, nextHeaderSizeT);
   if (res == SZ_OK)
   {
      res = SZ_ERROR_ARCHIVE;
      if (CrcCalc(buffer.data, nextHeaderSizeT) == nextHeaderCRC)
      {
         CSzData sd;
         uint64_t type;
         sd.Data = buffer.data;
         sd.Size = buffer.size;
         res = SzReadID(&sd, &type);
         if (res == SZ_OK)
         {
            if (type == k7zIdEncodedHeader)
            {
               CBuf outBuffer;
               Buf_Init(&outBuffer);
               res = SzReadAndDecodePackedStreams(inStream, &sd, &outBuffer, p->startPosAfterHeader, allocTemp);
               if (res != SZ_OK)
                  Buf_Free(&outBuffer, allocTemp);
               else
               {
                  Buf_Free(&buffer, allocTemp);
                  buffer.data = outBuffer.data;
                  buffer.size = outBuffer.size;
                  sd.Data = buffer.data;
                  sd.Size = buffer.size;
                  res = SzReadID(&sd, &type);
               }
            }
         }
         if (res == SZ_OK)
         {
            if (type == k7zIdHeader)
               res = SzReadHeader(p, &sd, allocMain, allocTemp);
            else
               res = SZ_ERROR_UNSUPPORTED;
         }
      }
   }
   Buf_Free(&buffer, allocTemp);
   return res;
}