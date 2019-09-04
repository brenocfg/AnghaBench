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
struct AVRC4 {int dummy; } ;

/* Variables and functions */
 struct AVRC4* av_rc4_alloc () ; 
 int /*<<< orphan*/  av_rc4_crypt (struct AVRC4*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rc4_init (struct AVRC4*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_rc4(uint8_t *output,
                              const uint8_t *input, unsigned size)
{
    static struct AVRC4 *rc4;
    if (!rc4 && !(rc4 = av_rc4_alloc()))
        fatal_error("out of memory");
    av_rc4_init(rc4, hardcoded_key, 128, 0);
    av_rc4_crypt(rc4, output, input, size, NULL, 0);
}