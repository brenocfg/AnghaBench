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
struct TYPE_3__ {unsigned int pregap_sectors; unsigned int stream_sector_size; scalar_t__ stream_sector_header_size; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ cdfs_track_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  intfstream_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdfs_seek_track_sector(cdfs_track_t* track, unsigned int sector)
{
   intfstream_seek(track->stream, (sector + track->pregap_sectors) * track->stream_sector_size + track->stream_sector_header_size, SEEK_SET);
}