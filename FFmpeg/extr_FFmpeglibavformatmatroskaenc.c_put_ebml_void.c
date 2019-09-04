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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  EBML_ID_VOID ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_ebml_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ebml_num (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void put_ebml_void(AVIOContext *pb, uint64_t size)
{
    int64_t currentpos = avio_tell(pb);

    av_assert0(size >= 2);

    put_ebml_id(pb, EBML_ID_VOID);
    // we need to subtract the length needed to store the size from the
    // size we need to reserve so 2 cases, we use 8 bytes to store the
    // size if possible, 1 byte otherwise
    if (size < 10)
        put_ebml_num(pb, size - 2, 0);
    else
        put_ebml_num(pb, size - 9, 8);
    ffio_fill(pb, 0, currentpos + size - avio_tell(pb));
}