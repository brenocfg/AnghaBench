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
struct TYPE_3__ {int /*<<< orphan*/ * streams; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int write_header(AVFormatContext *s)
{
    static const char *header = "# timecode format v2\n";
    avio_write(s->pb, header, strlen(header));
    avpriv_set_pts_info(s->streams[0], 64, 1, 1000);
    return 0;
}