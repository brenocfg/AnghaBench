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
struct AVCAST5 {int dummy; } ;

/* Variables and functions */
 struct AVCAST5* av_cast5_alloc () ; 
 int /*<<< orphan*/  av_cast5_crypt (struct AVCAST5*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_cast5_init (struct AVCAST5*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_cast128(uint8_t *output,
                             const uint8_t *input, unsigned size)
{
    static struct AVCAST5 *cast;
    if (!cast && !(cast = av_cast5_alloc()))
        fatal_error("out of memory");
    av_cast5_init(cast, hardcoded_key, 128);
    av_cast5_crypt(cast, output, input, size >> 3, 0);
}