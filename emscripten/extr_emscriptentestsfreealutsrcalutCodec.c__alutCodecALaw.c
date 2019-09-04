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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  ALvoid ;
typedef  int /*<<< orphan*/  ALint ;
typedef  int /*<<< orphan*/  ALfloat ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutBufferDataConstruct (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _alutMalloc (size_t) ; 
 int /*<<< orphan*/  alaw2linear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

ALvoid *_alutCodecALaw(ALvoid * data, size_t length, ALint numChannels, ALint bitsPerSample, ALfloat sampleFrequency)
{
  uint8_t *d = (uint8_t *) data;
  int16_t *buf = (int16_t *) _alutMalloc(length * 2);
  size_t i;

  if (buf == NULL)
  {
    return NULL;
  }
  for (i = 0; i < length; i++)
  {
    buf[i] = alaw2linear(d[i]);
  }
  free(data);
  return _alutBufferDataConstruct(buf, length * 2, numChannels, bitsPerSample, sampleFrequency);
}