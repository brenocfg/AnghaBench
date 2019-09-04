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
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  allocsize; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ucvector ;

/* Variables and functions */
 int /*<<< orphan*/  CERROR_TRY_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lodepng_chunk_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*) ; 
 unsigned char* lodepng_chunk_next (unsigned char*) ; 

__attribute__((used)) static unsigned addUnknownChunks(ucvector* out, unsigned char* data, size_t datasize)
{
  unsigned char* inchunk = data;
  while((size_t)(inchunk - data) < datasize)
  {
    CERROR_TRY_RETURN(lodepng_chunk_append(&out->data, &out->size, inchunk));
    out->allocsize = out->size; /*fix the allocsize again*/
    inchunk = lodepng_chunk_next(inchunk);
  }
  return 0;
}