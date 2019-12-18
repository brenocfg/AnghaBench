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
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void put_xiph_size(AVIOContext *pb, int size)
{
    ffio_fill(pb, 255, size / 255);
    avio_w8(pb, size % 255);
}