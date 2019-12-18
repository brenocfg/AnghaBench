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
struct AVTWOFISH {int dummy; } ;

/* Variables and functions */
 struct AVTWOFISH* av_twofish_alloc () ; 
 int /*<<< orphan*/  av_twofish_crypt (struct AVTWOFISH*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_twofish_init (struct AVTWOFISH*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_twofish(uint8_t *output,
                              const uint8_t *input, unsigned size)
{
    static struct AVTWOFISH *twofish;
    if (!twofish && !(twofish = av_twofish_alloc()))
        fatal_error("out of memory");
    av_twofish_init(twofish, hardcoded_key, 128);
    av_twofish_crypt(twofish, output, input, size >> 4, NULL, 0);
}