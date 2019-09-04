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
struct TYPE_3__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 char* var_read_string (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void var_read_metadata(AVFormatContext *avctx, const char *tag, int size)
{
    char *value = var_read_string(avctx->pb, size);
    if (value)
        av_dict_set(&avctx->metadata, tag, value, AV_DICT_DONT_STRDUP_VAL);
}