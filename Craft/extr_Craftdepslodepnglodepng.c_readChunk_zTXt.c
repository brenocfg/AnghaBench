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
struct TYPE_5__ {scalar_t__ data; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ ucvector ;
typedef  int /*<<< orphan*/  LodePNGInfo ;
typedef  int /*<<< orphan*/  LodePNGDecompressSettings ;

/* Variables and functions */
 int /*<<< orphan*/  CERROR_BREAK (unsigned int,int) ; 
 unsigned int lodepng_add_text (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  lodepng_free (char*) ; 
 scalar_t__ lodepng_malloc (unsigned int) ; 
 int /*<<< orphan*/  ucvector_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  ucvector_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ucvector_push_back (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int zlib_decompress (scalar_t__*,int /*<<< orphan*/ *,unsigned char*,unsigned int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static unsigned readChunk_zTXt(LodePNGInfo* info, const LodePNGDecompressSettings* zlibsettings,
                               const unsigned char* data, size_t chunkLength)
{
  unsigned error = 0;
  unsigned i;

  unsigned length, string2_begin;
  char *key = 0;
  ucvector decoded;

  ucvector_init(&decoded);

  while(!error) /*not really a while loop, only used to break on error*/
  {
    for(length = 0; length < chunkLength && data[length] != 0; length++) ;
    if(length + 2 >= chunkLength) CERROR_BREAK(error, 75); /*no null termination, corrupt?*/
    if(length < 1 || length > 79) CERROR_BREAK(error, 89); /*keyword too short or long*/

    key = (char*)lodepng_malloc(length + 1);
    if(!key) CERROR_BREAK(error, 83); /*alloc fail*/

    key[length] = 0;
    for(i = 0; i < length; i++) key[i] = data[i];

    if(data[length + 1] != 0) CERROR_BREAK(error, 72); /*the 0 byte indicating compression must be 0*/

    string2_begin = length + 2;
    if(string2_begin > chunkLength) CERROR_BREAK(error, 75); /*no null termination, corrupt?*/

    length = chunkLength - string2_begin;
    /*will fail if zlib error, e.g. if length is too small*/
    error = zlib_decompress(&decoded.data, &decoded.size,
                            (unsigned char*)(&data[string2_begin]),
                            length, zlibsettings);
    if(error) break;
    ucvector_push_back(&decoded, 0);

    error = lodepng_add_text(info, key, (char*)decoded.data);

    break;
  }

  lodepng_free(key);
  ucvector_cleanup(&decoded);

  return error;
}