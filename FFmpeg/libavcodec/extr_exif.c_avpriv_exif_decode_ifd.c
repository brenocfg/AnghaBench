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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int ff_exif_decode_ifd (void*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 

int avpriv_exif_decode_ifd(void *logctx, const uint8_t *buf, int size,
                           int le, int depth, AVDictionary **metadata)
{
    GetByteContext gb;

    bytestream2_init(&gb, buf, size);

    return ff_exif_decode_ifd(logctx, &gb, le, depth, metadata);
}