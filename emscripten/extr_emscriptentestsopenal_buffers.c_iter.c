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
typedef  int /*<<< orphan*/  ALuint ;
typedef  int ALint ;

/* Variables and functions */
 int /*<<< orphan*/  AL_BUFFERS_PROCESSED ; 
 int /*<<< orphan*/  AL_BUFFERS_QUEUED ; 
 scalar_t__ AL_NO_ERROR ; 
 int AL_PLAYING ; 
 int /*<<< orphan*/  AL_SOURCE_STATE ; 
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  alBufferData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ alGetError () ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  alSourceQueueBuffers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alSourceUnqueueBuffers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * data ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format ; 
 int /*<<< orphan*/  frequency ; 
 size_t offset ; 
 size_t size ; 
 int /*<<< orphan*/  source ; 

void iter() {
  ALuint buffer = 0;
  ALint buffersProcessed = 0;
  ALint buffersWereQueued = 0;
  ALint buffersQueued = 0;
  ALint state;
  float testPitch;

  alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffersProcessed);

  while (offset < size && buffersProcessed--) {
    // unqueue the old buffer and validate the queue length
    alGetSourcei(source, AL_BUFFERS_QUEUED, &buffersWereQueued);
    alSourceUnqueueBuffers(source, 1, &buffer);

    assert(alGetError() == AL_NO_ERROR);
    int len = size - offset;
    if (len > BUFFER_SIZE) {
      len = BUFFER_SIZE;
    }

    alGetSourcei(source, AL_BUFFERS_QUEUED, &buffersQueued);
    assert(buffersQueued == buffersWereQueued - 1);

    // queue the new buffer and validate the queue length
    buffersWereQueued = buffersQueued;
    alBufferData(buffer, format, &data[offset], len, frequency);

    alSourceQueueBuffers(source, 1, &buffer);
    assert(alGetError() == AL_NO_ERROR);

    alGetSourcei(source, AL_BUFFERS_QUEUED, &buffersQueued);
    assert(buffersQueued == buffersWereQueued + 1);

    // make sure it's still playing
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    assert(state == AL_PLAYING);

    offset += len;
  }

#ifdef TEST_ANIMATED_PITCH
  pitch *= .999;
  if (pitch < 0.5f)
    pitch = 0.5f;
  alSourcef(source, AL_PITCH, pitch);
  alGetSourcef(source, AL_PITCH, &testPitch);
  assert(pitch == testPitch);
#endif

  // Exit once we've processed the entire clip.
  if (offset >= size) {
#ifdef __EMSCRIPTEN__
    REPORT_RESULT(0);
#endif
    exit(0);
  }
}