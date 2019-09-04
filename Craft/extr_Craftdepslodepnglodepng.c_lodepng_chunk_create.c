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

/* Variables and functions */
 int /*<<< orphan*/  lodepng_chunk_generate_crc (unsigned char*) ; 
 scalar_t__ lodepng_realloc (unsigned char*,size_t) ; 
 int /*<<< orphan*/  lodepng_set32bitInt (unsigned char*,unsigned int) ; 

unsigned lodepng_chunk_create(unsigned char** out, size_t* outlength, unsigned length,
                              const char* type, const unsigned char* data)
{
  unsigned i;
  unsigned char *chunk, *new_buffer;
  size_t new_length = (*outlength) + length + 12;
  if(new_length < length + 12 || new_length < (*outlength)) return 77; /*integer overflow happened*/
  new_buffer = (unsigned char*)lodepng_realloc(*out, new_length);
  if(!new_buffer) return 83; /*alloc fail*/
  (*out) = new_buffer;
  (*outlength) = new_length;
  chunk = &(*out)[(*outlength) - length - 12];

  /*1: length*/
  lodepng_set32bitInt(chunk, (unsigned)length);

  /*2: chunk name (4 letters)*/
  chunk[4] = type[0];
  chunk[5] = type[1];
  chunk[6] = type[2];
  chunk[7] = type[3];

  /*3: the data*/
  for(i = 0; i < length; i++) chunk[8 + i] = data[i];

  /*4: CRC (of the chunkname characters and the data)*/
  lodepng_chunk_generate_crc(chunk);

  return 0;
}