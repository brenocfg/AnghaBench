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
 int /*<<< orphan*/  lodepng_chunk_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,char const*,unsigned char const*) ; 

__attribute__((used)) static unsigned addChunk(ucvector* out, const char* chunkName, const unsigned char* data, size_t length)
{
  CERROR_TRY_RETURN(lodepng_chunk_create(&out->data, &out->size, (unsigned)length, chunkName, data));
  out->allocsize = out->size; /*fix the allocsize again*/
  return 0;
}