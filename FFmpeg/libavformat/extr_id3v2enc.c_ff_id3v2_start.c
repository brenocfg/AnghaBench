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
struct TYPE_3__ {int version; int /*<<< orphan*/  size_pos; } ;
typedef  TYPE_1__ ID3v2EncContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  MKBETAG (char const,char const,char const,int) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ff_id3v2_start(ID3v2EncContext *id3, AVIOContext *pb, int id3v2_version,
                    const char *magic)
{
    id3->version = id3v2_version;

    avio_wb32(pb, MKBETAG(magic[0], magic[1], magic[2], id3v2_version));
    avio_w8(pb, 0);
    avio_w8(pb, 0); /* flags */

    /* reserve space for size */
    id3->size_pos = avio_tell(pb);
    avio_wb32(pb, 0);
}