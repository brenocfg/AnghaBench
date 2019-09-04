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
typedef  int /*<<< orphan*/  wrap ;
typedef  int /*<<< orphan*/  uint8_t ;
struct SwrContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  testxmmclobbers (int /*<<< orphan*/  (*) (struct SwrContext*,int /*<<< orphan*/ **,int,int /*<<< orphan*/  const**,int),struct SwrContext*,int /*<<< orphan*/ **,int,int /*<<< orphan*/  const**,int) ; 

wrap(swr_convert(struct SwrContext *s, uint8_t **out, int out_count,
                 const uint8_t **in , int in_count))
{
    testxmmclobbers(swr_convert, s, out, out_count, in, in_count);
}