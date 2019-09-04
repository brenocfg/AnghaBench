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
struct AVAES {int dummy; } ;

/* Variables and functions */
 struct AVAES* av_aes_alloc () ; 
 int /*<<< orphan*/  av_aes_crypt (struct AVAES*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_aes_init (struct AVAES*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_aes128(uint8_t *output,
                            const uint8_t *input, unsigned size)
{
    static struct AVAES *aes;
    if (!aes && !(aes = av_aes_alloc()))
        fatal_error("out of memory");
    av_aes_init(aes, hardcoded_key, 128, 0);
    av_aes_crypt(aes, output, input, size >> 4, NULL, 0);
}