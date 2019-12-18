#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_4__ {TYPE_3__ inflater; int /*<<< orphan*/  allocator; } ;
typedef  TYPE_1__ zlib_codec_data ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  chd_error ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  CHDERR_CODEC_ERROR ; 
 int /*<<< orphan*/  CHDERR_NONE ; 
 int /*<<< orphan*/  CHDERR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 int Z_MEM_ERROR ; 
 int Z_OK ; 
 int inflateInit2 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zlib_fast_alloc ; 
 int /*<<< orphan*/  zlib_fast_free ; 

chd_error zlib_codec_init(void *codec, uint32_t hunkbytes)
{
	int zerr;
	chd_error err;
	zlib_codec_data *data = (zlib_codec_data*)codec;

	/* clear the buffers */
	memset(data, 0, sizeof(zlib_codec_data));

	/* init the inflater first */
	data->inflater.next_in = (Bytef *)data;	/* bogus, but that's ok */
	data->inflater.avail_in = 0;
	data->inflater.zalloc = zlib_fast_alloc;
	data->inflater.zfree = zlib_fast_free;
	data->inflater.opaque = &data->allocator;
	zerr = inflateInit2(&data->inflater, -MAX_WBITS);

	/* convert errors */
	if (zerr == Z_MEM_ERROR)
		err = CHDERR_OUT_OF_MEMORY;
	else if (zerr != Z_OK)
		err = CHDERR_CODEC_ERROR;
	else
		err = CHDERR_NONE;

	return err;
}