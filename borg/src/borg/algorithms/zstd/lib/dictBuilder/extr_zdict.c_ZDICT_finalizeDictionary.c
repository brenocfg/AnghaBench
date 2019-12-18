#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int compressionLevel; unsigned int notificationLevel; unsigned int const dictID; } ;
typedef  TYPE_1__ ZDICT_params_t ;
typedef  unsigned int U64 ;
typedef  unsigned int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int HBUFFSIZE ; 
 int /*<<< orphan*/  MEM_writeLE32 (int /*<<< orphan*/ *,unsigned int const) ; 
 unsigned int XXH64 (void const*,size_t,int /*<<< orphan*/ ) ; 
 size_t ZDICT_CONTENTSIZE_MIN ; 
 size_t ZDICT_DICTSIZE_MIN ; 
 size_t ZDICT_analyzeEntropy (int /*<<< orphan*/ *,int,int const,void const*,size_t const*,unsigned int,void const*,size_t,unsigned int const) ; 
 scalar_t__ ZDICT_isError (size_t const) ; 
 unsigned int const ZSTD_MAGIC_DICTIONARY ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int g_compressionLevel_default ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memmove (char*,void const*,size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

size_t ZDICT_finalizeDictionary(void* dictBuffer, size_t dictBufferCapacity,
                          const void* customDictContent, size_t dictContentSize,
                          const void* samplesBuffer, const size_t* samplesSizes,
                          unsigned nbSamples, ZDICT_params_t params)
{
    size_t hSize;
#define HBUFFSIZE 256   /* should prove large enough for all entropy headers */
    BYTE header[HBUFFSIZE];
    int const compressionLevel = (params.compressionLevel == 0) ? g_compressionLevel_default : params.compressionLevel;
    U32 const notificationLevel = params.notificationLevel;

    /* check conditions */
    DEBUGLOG(4, "ZDICT_finalizeDictionary");
    if (dictBufferCapacity < dictContentSize) return ERROR(dstSize_tooSmall);
    if (dictContentSize < ZDICT_CONTENTSIZE_MIN) return ERROR(srcSize_wrong);
    if (dictBufferCapacity < ZDICT_DICTSIZE_MIN) return ERROR(dstSize_tooSmall);

    /* dictionary header */
    MEM_writeLE32(header, ZSTD_MAGIC_DICTIONARY);
    {   U64 const randomID = XXH64(customDictContent, dictContentSize, 0);
        U32 const compliantID = (randomID % ((1U<<31)-32768)) + 32768;
        U32 const dictID = params.dictID ? params.dictID : compliantID;
        MEM_writeLE32(header+4, dictID);
    }
    hSize = 8;

    /* entropy tables */
    DISPLAYLEVEL(2, "\r%70s\r", "");   /* clean display line */
    DISPLAYLEVEL(2, "statistics ... \n");
    {   size_t const eSize = ZDICT_analyzeEntropy(header+hSize, HBUFFSIZE-hSize,
                                  compressionLevel,
                                  samplesBuffer, samplesSizes, nbSamples,
                                  customDictContent, dictContentSize,
                                  notificationLevel);
        if (ZDICT_isError(eSize)) return eSize;
        hSize += eSize;
    }

    /* copy elements in final buffer ; note : src and dst buffer can overlap */
    if (hSize + dictContentSize > dictBufferCapacity) dictContentSize = dictBufferCapacity - hSize;
    {   size_t const dictSize = hSize + dictContentSize;
        char* dictEnd = (char*)dictBuffer + dictSize;
        memmove(dictEnd - dictContentSize, customDictContent, dictContentSize);
        memcpy(dictBuffer, header, hSize);
        return dictSize;
    }
}