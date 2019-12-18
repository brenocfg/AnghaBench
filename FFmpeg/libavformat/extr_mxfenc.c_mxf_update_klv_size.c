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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  klv_encode_ber4_length (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mxf_update_klv_size(AVIOContext *pb, int64_t pos)
{
    int64_t cur_pos = avio_tell(pb);
    int size = cur_pos - pos;
    avio_seek(pb, pos - 4, SEEK_SET);
    klv_encode_ber4_length(pb, size);
    avio_seek(pb, cur_pos, SEEK_SET);
}