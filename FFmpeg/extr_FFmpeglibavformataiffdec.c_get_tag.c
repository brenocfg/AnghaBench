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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rl32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_tag(AVIOContext *pb, uint32_t * tag)
{
    int size;

    if (avio_feof(pb))
        return AVERROR(EIO);

    *tag = avio_rl32(pb);
    size = avio_rb32(pb);

    if (size < 0)
        size = 0x7fffffff;

    return size;
}