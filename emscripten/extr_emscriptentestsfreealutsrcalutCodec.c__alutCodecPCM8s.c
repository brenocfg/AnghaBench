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
typedef  scalar_t__ int8_t ;
typedef  int /*<<< orphan*/  ALvoid ;
typedef  int /*<<< orphan*/  ALint ;
typedef  int /*<<< orphan*/  ALfloat ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutBufferDataConstruct (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ALvoid *_alutCodecPCM8s(ALvoid * data, size_t length, ALint numChannels, ALint bitsPerSample, ALfloat sampleFrequency)
{
  int8_t *d = (int8_t *) data;
  size_t i;

  for (i = 0; i < length; i++)
  {
    d[i] += (int8_t) 128;
  }
  return _alutBufferDataConstruct(data, length, numChannels, bitsPerSample, sampleFrequency);
}