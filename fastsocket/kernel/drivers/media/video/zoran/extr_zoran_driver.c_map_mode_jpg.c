#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num_buffers; int /*<<< orphan*/  buffer_size; } ;
struct zoran_fh {TYPE_1__ buffers; int /*<<< orphan*/  map_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZORAN_MAP_MODE_JPG_PLAY ; 
 int /*<<< orphan*/  ZORAN_MAP_MODE_JPG_REC ; 
 int /*<<< orphan*/  jpg_bufsize ; 
 int /*<<< orphan*/  jpg_nbufs ; 

__attribute__((used)) static void map_mode_jpg(struct zoran_fh *fh, int play)
{
	fh->map_mode = play ? ZORAN_MAP_MODE_JPG_PLAY : ZORAN_MAP_MODE_JPG_REC;
	fh->buffers.buffer_size = jpg_bufsize;
	fh->buffers.num_buffers = jpg_nbufs;
}