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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  ALuint ;
typedef  int ALint ;

/* Variables and functions */
 int AL_BUFFERS_QUEUED ; 
 scalar_t__ AL_FORMAT_MONO16 ; 
 scalar_t__ AL_FORMAT_MONO8 ; 
 scalar_t__ AL_FORMAT_STEREO16 ; 
 scalar_t__ AL_FORMAT_STEREO8 ; 
 scalar_t__ AL_NO_ERROR ; 
 int /*<<< orphan*/  AL_PITCH ; 
 int AL_PLAYING ; 
 int AL_SOURCE_STATE ; 
 int BUFFER_SIZE ; 
 int NUM_BUFFERS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  alBufferData (int /*<<< orphan*/ ,scalar_t__,int*,int,int) ; 
 int /*<<< orphan*/  alGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alGenSources (int,int /*<<< orphan*/ *) ; 
 scalar_t__ alGetError () ; 
 int /*<<< orphan*/  alGetSourcef (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  alGetSourcei (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  alSourcePlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alSourceQueueBuffers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alSourcef (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  alcCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alcMakeContextCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcOpenDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bits ; 
 int channels ; 
 int /*<<< orphan*/  context ; 
 int* data ; 
 int /*<<< orphan*/  device ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ format ; 
 int /*<<< orphan*/  fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int frequency ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iter () ; 
 scalar_t__ malloc (int) ; 
 int offset ; 
 float pitch ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int size ; 
 int /*<<< orphan*/  source ; 
 int /*<<< orphan*/  usleep (int) ; 

int main(int argc, char* argv[]) {
  float testPitch;
  //
  // Setup the AL context.
  //
  device = alcOpenDevice(NULL);
  context = alcCreateContext(device, NULL);
  alcMakeContextCurrent(context);

  //
  // Read in the audio sample.
  //
#ifdef __EMSCRIPTEN__
  FILE* fp = fopen("the_entertainer.wav", "rb");
#else
  FILE* fp = fopen("sounds/the_entertainer.wav", "rb");
#endif
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  data = (unsigned char*)malloc(size);
  fread(data, size, 1, fp);
  fclose(fp);

  offset = 12; // ignore the RIFF header
  offset += 8; // ignore the fmt header
  offset += 2; // ignore the format type

  channels = data[offset + 1] << 8;
  channels |= data[offset];
  offset += 2;
  printf("Channels: %u\n", channels);

  frequency = data[offset + 3] << 24;
  frequency |= data[offset + 2] << 16;
  frequency |= data[offset + 1] << 8;
  frequency |= data[offset];
  offset += 4;
  printf("Frequency: %u\n", frequency);

  offset += 6; // ignore block size and bps

  bits = data[offset + 1] << 8;
  bits |= data[offset];
  offset += 2;
  printf("Bits: %u\n", bits);

  format = 0;
  if (bits == 8) {
    if (channels == 1) {
      format = AL_FORMAT_MONO8;
    } else if (channels == 2) {
      format = AL_FORMAT_STEREO8;
    }
  } else if (bits == 16) {
    if (channels == 1) {
      format = AL_FORMAT_MONO16;
    } else if (channels == 2) {
      format = AL_FORMAT_STEREO16;
    }
  }
  offset += 8; // ignore the data chunk

  //
  // Seed the buffers with some initial data.
  //
  ALuint buffers[NUM_BUFFERS];
  alGenBuffers(NUM_BUFFERS, buffers);
  alGenSources(1, &source);

  alSourcef(source, AL_PITCH, pitch);
  alGetSourcef(source, AL_PITCH, &testPitch);
  assert(pitch == testPitch);

  ALint numBuffers = 0;
  while (numBuffers < NUM_BUFFERS && offset < size) {
    int len = size - offset;
    if (len > BUFFER_SIZE) {
      len = BUFFER_SIZE;
    }

    alBufferData(buffers[numBuffers], format, &data[offset], len, frequency);
    alSourceQueueBuffers(source, 1, &buffers[numBuffers]);
    assert(alGetError() == AL_NO_ERROR);

    offset += len;
    numBuffers++;
  }

  ALint srcLen = 0;
  alGetSourcei(source, 0x2009 /* AL_BYTE_LENGTH_SOFT */, &srcLen);
  assert(srcLen == NUM_BUFFERS * BUFFER_SIZE);

#ifdef TEST_ANIMATED_PITCH
  printf("You should hear a clip of the 1902 piano song \"The Entertainer\" played back at a high pitch rate, and animated to slow down to half playback speed.\n");
#else
  printf("You should hear a clip of the 1902 piano song \"The Entertainer\" played back at half speed.\n");
#endif

  //
  // Start playing the source.
  //
  alSourcePlay(source);

  ALint state;
  alGetSourcei(source, AL_SOURCE_STATE, &state);
  assert(state == AL_PLAYING);

  alGetSourcei(source, AL_BUFFERS_QUEUED, &numBuffers);
  assert(numBuffers == NUM_BUFFERS);

  //
  // Cycle and refill the buffers until we're done.
  //
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(iter, 0, 0);
#else
  while (1) {
    iter();
    usleep(16);
  }
#endif
}