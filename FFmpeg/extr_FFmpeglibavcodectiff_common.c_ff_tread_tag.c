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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 unsigned int FF_ARRAY_ELEMS (unsigned int*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 unsigned int TIFF_STRING ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 unsigned int ff_tget_long (int /*<<< orphan*/ *,int) ; 
 unsigned int ff_tget_short (int /*<<< orphan*/ *,int) ; 
 int ff_tis_ifd (unsigned int) ; 
 unsigned int* type_sizes ; 

int ff_tread_tag(GetByteContext *gb, int le, unsigned *tag, unsigned *type,
                 unsigned *count, int *next)
{
    int ifd_tag;
    int valid_type;

    *tag    = ff_tget_short(gb, le);
    *type   = ff_tget_short(gb, le);
    *count  = ff_tget_long (gb, le);

    ifd_tag    = ff_tis_ifd(*tag);
    valid_type = *type != 0 && *type < FF_ARRAY_ELEMS(type_sizes);

    *next = bytestream2_tell(gb) + 4;

    // check for valid type
    if (!valid_type) {
        return AVERROR_INVALIDDATA;
    }

    // seek to offset if this is an IFD-tag or
    // if count values do not fit into the offset value
    if (ifd_tag || (*count > 4 || !(type_sizes[*type] * (*count) <= 4 || *type == TIFF_STRING))) {
        bytestream2_seek(gb, ff_tget_long (gb, le), SEEK_SET);
    }

    return 0;
}