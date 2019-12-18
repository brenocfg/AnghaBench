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
struct AVBlowfish {int dummy; } ;

/* Variables and functions */
 struct AVBlowfish* av_blowfish_alloc () ; 
 int /*<<< orphan*/  av_blowfish_crypt (struct AVBlowfish*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_blowfish_init (struct AVBlowfish*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_blowfish(uint8_t *output,
                              const uint8_t *input, unsigned size)
{
    static struct AVBlowfish *blowfish;
    if (!blowfish && !(blowfish = av_blowfish_alloc()))
        fatal_error("out of memory");
    av_blowfish_init(blowfish, hardcoded_key, 16);
    av_blowfish_crypt(blowfish, output, input, size >> 3, NULL, 0);
}