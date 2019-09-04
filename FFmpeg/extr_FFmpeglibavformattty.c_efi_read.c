#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  fsize; } ;
typedef  TYPE_1__ TtyDemuxContext ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efi_read(AVFormatContext *avctx, uint64_t start_pos)
{
    TtyDemuxContext *s = avctx->priv_data;
    AVIOContext *pb = avctx->pb;
    char buf[37];
    int len;

    avio_seek(pb, start_pos, SEEK_SET);
    if (avio_r8(pb) != 0x1A)
        return -1;

#define GET_EFI_META(name,size) \
    len = avio_r8(pb); \
    if (len < 1 || len > size) \
        return -1; \
    if (avio_read(pb, buf, size) == size) { \
        buf[len] = 0; \
        av_dict_set(&avctx->metadata, name, buf, 0); \
    }

    GET_EFI_META("filename", 12)
    GET_EFI_META("title",    36)

    s->fsize = start_pos;
    return 0;
}