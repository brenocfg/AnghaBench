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
 int /*<<< orphan*/  avio_put_str16le (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_metadata_guid ; 
 int /*<<< orphan*/  ff_put_guid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_metadata_header(AVIOContext *pb, int type, const char *key, int value_size)
{
    ff_put_guid(pb, &ff_metadata_guid);
    avio_wl32(pb, type);
    avio_wl32(pb, value_size);
    avio_put_str16le(pb, key);
}