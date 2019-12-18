#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* allocptr; } ;
struct TYPE_3__ {TYPE_2__ allocator; int /*<<< orphan*/  inflater; } ;
typedef  TYPE_1__ zlib_codec_data ;
typedef  TYPE_2__ zlib_allocator ;

/* Variables and functions */
 int MAX_ZLIB_ALLOCS ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 

void zlib_codec_free(void *codec)
{
	zlib_codec_data *data = (zlib_codec_data *)codec;

	/* deinit the streams */
	if (data != NULL)
	{
		int i;
      zlib_allocator alloc;

		inflateEnd(&data->inflater);

		/* free our fast memory */
		alloc = data->allocator;
		for (i = 0; i < MAX_ZLIB_ALLOCS; i++)
			if (alloc.allocptr[i])
				free(alloc.allocptr[i]);
	}
}