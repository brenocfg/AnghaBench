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
struct AVDES {int dummy; } ;

/* Variables and functions */
 struct AVDES* av_des_alloc () ; 
 int /*<<< orphan*/  av_des_crypt (struct AVDES*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_des_init (struct AVDES*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  hardcoded_key ; 

__attribute__((used)) static void run_lavu_des(uint8_t *output,
                              const uint8_t *input, unsigned size)
{
    static struct AVDES *des;
    if (!des && !(des = av_des_alloc()))
        fatal_error("out of memory");
    av_des_init(des, hardcoded_key, 64, 0);
    av_des_crypt(des, output, input, size >> 3, NULL, 0);
}