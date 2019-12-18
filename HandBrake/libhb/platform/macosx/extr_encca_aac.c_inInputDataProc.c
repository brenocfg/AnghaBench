#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int isamplesiz; int /*<<< orphan*/  remap; scalar_t__ ibytes; int /*<<< orphan*/  list; int /*<<< orphan*/ * buf; scalar_t__ input_done; } ;
typedef  TYPE_2__ hb_work_private_t ;
typedef  int UInt32 ;
struct TYPE_7__ {TYPE_1__* mBuffers; } ;
struct TYPE_5__ {int mDataByteSize; int /*<<< orphan*/ * mData; } ;
typedef  int OSStatus ;
typedef  int /*<<< orphan*/  AudioStreamPacketDescription ;
typedef  int /*<<< orphan*/  AudioConverterRef ;
typedef  TYPE_3__ AudioBufferList ;

/* Variables and functions */
 int MIN (scalar_t__,int) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_audio_remap (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int hb_list_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_getbytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int noErr ; 

__attribute__((used)) static OSStatus inInputDataProc(AudioConverterRef converter, UInt32 *npackets,
                                AudioBufferList *buffers,
                                AudioStreamPacketDescription **ignored,
                                void *userdata)
{
    hb_work_private_t *pv = userdata;

    if (!pv->ibytes)
    {
        *npackets = 0;
        if (pv->input_done)
        {
            // EOF on input
            buffers->mBuffers[0].mDataByteSize = 0;
            return noErr;
        }
        else
        {
            // Not enough data available
            return 1;
        }
    }

    if (pv->buf != NULL)
    {
        free(pv->buf);
    }

    buffers->mBuffers[0].mDataByteSize = MIN(pv->ibytes,
                                             pv->isamplesiz * *npackets);
    pv->buf = calloc(1, buffers->mBuffers[0].mDataByteSize);
    buffers->mBuffers[0].mData = pv->buf;

    if (hb_list_bytes(pv->list) >= buffers->mBuffers[0].mDataByteSize)
    {
        hb_list_getbytes(pv->list, buffers->mBuffers[0].mData,
                         buffers->mBuffers[0].mDataByteSize, NULL, NULL);
    }
    else
    {
        *npackets = 0;
        return 1;
    }

    *npackets = buffers->mBuffers[0].mDataByteSize / pv->isamplesiz;
    pv->ibytes -= buffers->mBuffers[0].mDataByteSize;

    hb_audio_remap(pv->remap, (uint8_t**)(&buffers->mBuffers[0].mData),
                   (int)(*npackets));

    return noErr;
}