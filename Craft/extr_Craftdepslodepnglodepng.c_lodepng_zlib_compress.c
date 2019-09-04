#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* data; size_t size; } ;
typedef  TYPE_1__ ucvector ;
typedef  int /*<<< orphan*/  LodePNGCompressSettings ;

/* Variables and functions */
 unsigned int adler32 (unsigned char const*,unsigned int) ; 
 unsigned int deflate (unsigned char**,size_t*,unsigned char const*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lodepng_add32bitInt (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  lodepng_free (unsigned char*) ; 
 int /*<<< orphan*/  ucvector_init_buffer (TYPE_1__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ucvector_push_back (TYPE_1__*,unsigned char) ; 

unsigned lodepng_zlib_compress(unsigned char** out, size_t* outsize, const unsigned char* in,
                               size_t insize, const LodePNGCompressSettings* settings)
{
  /*initially, *out must be NULL and outsize 0, if you just give some random *out
  that's pointing to a non allocated buffer, this'll crash*/
  ucvector outv;
  size_t i;
  unsigned error;
  unsigned char* deflatedata = 0;
  size_t deflatesize = 0;

  unsigned ADLER32;
  /*zlib data: 1 byte CMF (CM+CINFO), 1 byte FLG, deflate data, 4 byte ADLER32 checksum of the Decompressed data*/
  unsigned CMF = 120; /*0b01111000: CM 8, CINFO 7. With CINFO 7, any window size up to 32768 can be used.*/
  unsigned FLEVEL = 0;
  unsigned FDICT = 0;
  unsigned CMFFLG = 256 * CMF + FDICT * 32 + FLEVEL * 64;
  unsigned FCHECK = 31 - CMFFLG % 31;
  CMFFLG += FCHECK;

  /*ucvector-controlled version of the output buffer, for dynamic array*/
  ucvector_init_buffer(&outv, *out, *outsize);

  ucvector_push_back(&outv, (unsigned char)(CMFFLG / 256));
  ucvector_push_back(&outv, (unsigned char)(CMFFLG % 256));

  error = deflate(&deflatedata, &deflatesize, in, insize, settings);

  if(!error)
  {
    ADLER32 = adler32(in, (unsigned)insize);
    for(i = 0; i < deflatesize; i++) ucvector_push_back(&outv, deflatedata[i]);
    lodepng_free(deflatedata);
    lodepng_add32bitInt(&outv, ADLER32);
  }

  *out = outv.data;
  *outsize = outv.size;

  return error;
}