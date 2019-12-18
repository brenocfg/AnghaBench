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
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void put_amf_string(AVIOContext *pb, const char *str)
{
    size_t len = strlen(str);
    avio_wb16(pb, len);
    avio_write(pb, str, len);
}