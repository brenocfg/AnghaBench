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
struct TYPE_3__ {size_t length; int /*<<< orphan*/  sampleFrequency; void* bitsPerSample; void* numChannels; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ BufferData ;
typedef  int /*<<< orphan*/  ALvoid ;
typedef  void* ALint ;
typedef  int /*<<< orphan*/  ALfloat ;

/* Variables and functions */
 scalar_t__ _alutMalloc (int) ; 

BufferData *_alutBufferDataConstruct(ALvoid * data, size_t length, ALint numChannels, ALint bitsPerSample, ALfloat sampleFrequency)
{
  BufferData *bufferData = (BufferData *) _alutMalloc(sizeof(BufferData));

  if (bufferData == NULL)
  {
    return NULL;
  }

  bufferData->data = data;
  bufferData->length = length;
  bufferData->numChannels = numChannels;
  bufferData->bitsPerSample = bitsPerSample;
  bufferData->sampleFrequency = sampleFrequency;

  return bufferData;
}