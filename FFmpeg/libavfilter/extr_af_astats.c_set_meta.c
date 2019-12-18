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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  key2 ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char const*,...) ; 

__attribute__((used)) static void set_meta(AVDictionary **metadata, int chan, const char *key,
                     const char *fmt, double val)
{
    uint8_t value[128];
    uint8_t key2[128];

    snprintf(value, sizeof(value), fmt, val);
    if (chan)
        snprintf(key2, sizeof(key2), "lavfi.astats.%d.%s", chan, key);
    else
        snprintf(key2, sizeof(key2), "lavfi.astats.%s", key);
    av_dict_set(metadata, key2, value, 0);
}