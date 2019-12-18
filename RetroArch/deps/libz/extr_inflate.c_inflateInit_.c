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
 int /*<<< orphan*/  DEF_WBITS ; 
 int inflateInit2_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

int inflateInit_(z_streamp strm, const char *version, int stream_size)
{
   return inflateInit2_(strm, DEF_WBITS, version, stream_size);
}