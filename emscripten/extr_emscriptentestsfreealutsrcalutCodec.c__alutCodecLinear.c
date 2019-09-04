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
typedef  int /*<<< orphan*/  ALvoid ;
typedef  int /*<<< orphan*/  ALint ;
typedef  int /*<<< orphan*/  ALfloat ;

/* Variables and functions */
 int /*<<< orphan*/ * _alutBufferDataConstruct (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ALvoid *_alutCodecLinear(ALvoid * data, size_t length, ALint numChannels, ALint bitsPerSample, ALfloat sampleFrequency)
{
  return _alutBufferDataConstruct(data, length, numChannels, bitsPerSample, sampleFrequency);
}