#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size_in_bits; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int get_bits1 (TYPE_1__*) ; 
 scalar_t__ get_bits_count (TYPE_1__*) ; 

__attribute__((used)) static inline int check_marker(void *logctx, GetBitContext *s, const char *msg)
{
    int bit = get_bits1(s);
    if (!bit)
        av_log(logctx, AV_LOG_INFO, "Marker bit missing at %d of %d %s\n",
               get_bits_count(s) - 1, s->size_in_bits, msg);

    return bit;
}