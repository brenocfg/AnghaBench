#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  biCompression; } ;
typedef  TYPE_1__ BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  biBitCount ; 
 int /*<<< orphan*/  biClrImportant ; 
 int /*<<< orphan*/  biClrUsed ; 
 int /*<<< orphan*/  biCompression ; 
 int /*<<< orphan*/  biHeight ; 
 int /*<<< orphan*/  biPlanes ; 
 int /*<<< orphan*/  biSize ; 
 int /*<<< orphan*/  biSizeImage ; 
 int /*<<< orphan*/  biWidth ; 
 int /*<<< orphan*/  biXPelsPerMeter ; 
 int /*<<< orphan*/  biYPelsPerMeter ; 
 int /*<<< orphan*/  dstruct (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dump_bih(AVFormatContext *s, BITMAPINFOHEADER *bih)
{
    av_log(s, AV_LOG_DEBUG, "BITMAPINFOHEADER\n");
    dstruct(s, bih, biSize, "lu");
    dstruct(s, bih, biWidth, "ld");
    dstruct(s, bih, biHeight, "ld");
    dstruct(s, bih, biPlanes, "d");
    dstruct(s, bih, biBitCount, "d");
    dstruct(s, bih, biCompression, "lu");
    av_log(s, AV_LOG_DEBUG, "    biCompression:\t\"%.4s\"\n",
                   (char*) &bih->biCompression);
    dstruct(s, bih, biSizeImage, "lu");
    dstruct(s, bih, biXPelsPerMeter, "lu");
    dstruct(s, bih, biYPelsPerMeter, "lu");
    dstruct(s, bih, biClrUsed, "lu");
    dstruct(s, bih, biClrImportant, "lu");
}