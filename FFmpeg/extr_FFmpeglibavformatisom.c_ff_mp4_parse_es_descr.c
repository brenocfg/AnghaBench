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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

void ff_mp4_parse_es_descr(AVIOContext *pb, int *es_id)
{
     int flags;
     if (es_id) *es_id = avio_rb16(pb);
     else                avio_rb16(pb);
     flags = avio_r8(pb);
     if (flags & 0x80) //streamDependenceFlag
         avio_rb16(pb);
     if (flags & 0x40) { //URL_Flag
         int len = avio_r8(pb);
         avio_skip(pb, len);
     }
     if (flags & 0x20) //OCRstreamFlag
         avio_rb16(pb);
}