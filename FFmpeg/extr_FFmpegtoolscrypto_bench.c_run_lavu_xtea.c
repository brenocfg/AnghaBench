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
struct AVXTEA {int dummy; } ;

/* Variables and functions */
 struct AVXTEA* av_xtea_alloc () ; 
 int /*<<< orphan*/  av_xtea_crypt (struct AVXTEA*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_xtea_init (struct AVXTEA*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_xtea(uint8_t *output,
                              const uint8_t *input, unsigned size)
{
    static struct AVXTEA *xtea;
    if (!xtea && !(xtea = av_xtea_alloc()))
        fatal_error("out of memory");
    av_xtea_init(xtea, hardcoded_key);
    av_xtea_crypt(xtea, output, input, size >> 3, NULL, 0);
}