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
typedef  int /*<<< orphan*/  uint8_t ;
struct AVCAMELLIA {int dummy; } ;

/* Variables and functions */
 struct AVCAMELLIA* av_camellia_alloc () ; 
 int /*<<< orphan*/  av_camellia_crypt (struct AVCAMELLIA*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_camellia_init (struct AVCAMELLIA*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_camellia(uint8_t *output,
                              const uint8_t *input, unsigned size)
{
    static struct AVCAMELLIA *camellia;
    if (!camellia && !(camellia = av_camellia_alloc()))
        fatal_error("out of memory");
    av_camellia_init(camellia, hardcoded_key, 128);
    av_camellia_crypt(camellia, output, input, size >> 4, NULL, 0);
}