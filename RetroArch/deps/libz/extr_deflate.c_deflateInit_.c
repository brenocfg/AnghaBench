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
typedef  int /*<<< orphan*/  z_streamp ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_MEM_LEVEL ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 int /*<<< orphan*/  Z_DEFAULT_STRATEGY ; 
 int /*<<< orphan*/  Z_DEFLATED ; 
 int deflateInit2_ (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

int deflateInit_(z_streamp strm, int level, const char *version, int stream_size)
{
   return deflateInit2_(strm, level, Z_DEFLATED, MAX_WBITS, DEF_MEM_LEVEL,
         Z_DEFAULT_STRATEGY, version, stream_size);
   /* To do: ignore strm->next_in if we use it as window */
}