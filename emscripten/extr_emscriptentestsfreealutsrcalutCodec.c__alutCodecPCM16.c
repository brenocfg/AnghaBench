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
typedef  int int16_t ;
typedef  int /*<<< orphan*/  ALvoid ;
typedef  int /*<<< orphan*/  ALint ;
typedef  int /*<<< orphan*/  ALfloat ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutBufferDataConstruct (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ALvoid *_alutCodecPCM16(ALvoid * data, size_t length, ALint numChannels, ALint bitsPerSample, ALfloat sampleFrequency)
{
  int16_t *d = (int16_t *) data;
  size_t i, l = length / 2;

  for (i = 0; i < l; i++)
  {
    int16_t x = d[i];

    d[i] = ((x << 8) & 0xFF00) | ((x >> 8) & 0x00FF);
  }
  return _alutBufferDataConstruct(data, length, numChannels, bitsPerSample, sampleFrequency);
}