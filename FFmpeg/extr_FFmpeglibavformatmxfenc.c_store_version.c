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
struct TYPE_3__ {int flags; int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVFMT_FLAG_BITEXACT ; 
 int /*<<< orphan*/  LIBAVFORMAT_VERSION_MAJOR ; 
 int /*<<< orphan*/  LIBAVFORMAT_VERSION_MICRO ; 
 int /*<<< orphan*/  LIBAVFORMAT_VERSION_MINOR ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void store_version(AVFormatContext *s){
    AVIOContext *pb = s->pb;

    if (s->flags & AVFMT_FLAG_BITEXACT) {
        avio_wb16(pb, 0); // major
        avio_wb16(pb, 0); // minor
        avio_wb16(pb, 0); // tertiary
    } else {
        avio_wb16(pb, LIBAVFORMAT_VERSION_MAJOR); // major
        avio_wb16(pb, LIBAVFORMAT_VERSION_MINOR); // minor
        avio_wb16(pb, LIBAVFORMAT_VERSION_MICRO); // tertiary
    }
    avio_wb16(pb, 0); // patch
    avio_wb16(pb, 0); // release
}