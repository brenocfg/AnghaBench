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
struct TYPE_3__ {int extradata_size; scalar_t__ extradata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int put_wv_codecpriv(AVIOContext *pb, AVCodecParameters *par)
{
    if (par->extradata && par->extradata_size == 2)
        avio_write(pb, par->extradata, 2);
    else
        avio_wl16(pb, 0x403); // fallback to the version mentioned in matroska specs
    return 0;
}