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
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int bytestream2_tell_p (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lz_copy(PutByteContext *pb, GetByteContext *g2, int offset, unsigned len)
{
    int i;

    if (offset == -1) {
        int c;

        bytestream2_seek(g2, bytestream2_tell_p(pb) - 1, SEEK_SET);
        c = bytestream2_get_byte(g2);
        for (i = 0; i < len; i++) {
            bytestream2_put_byte(pb, c);
        }
    } else if (offset < 0) {
        int start = bytestream2_tell_p(pb) - (-offset);

        bytestream2_seek(g2, start, SEEK_SET);
        for (i = 0; i < len; i++) {
            bytestream2_put_byte(pb, bytestream2_get_byte(g2));
        }
    } else {
        int start = bytestream2_tell_p(pb) + offset;

        bytestream2_seek(g2, start, SEEK_SET);
        for (i = 0; i < len; i++) {
            bytestream2_put_byte(pb, bytestream2_get_byte(g2));
        }
    }
}