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
 int avio_get_str (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void get_strl(AVIOContext *pb, char *buf, int buf_size, int len)
{
    int read = avio_get_str(pb, len, buf, buf_size);

    if (read > 0)
        avio_skip(pb, len - read);
}